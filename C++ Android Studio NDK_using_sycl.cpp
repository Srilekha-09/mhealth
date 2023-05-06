#include <jni.h>
#include <string>
#include <vector>
#include "xml/etree.h"
#include "openvino/inference_engine.hpp"
#include "daal4py/svd.hpp"
#include "daal4py/pca.hpp"
#include <CL/sycl.hpp>

namespace sycl = cl::sycl;

extern "C" JNIEXPORT jobjectArray JNICALL Java_com_example_myapp_AngleDetector_detectAngle(
        JNIEnv *env,
        jclass /* this */,
        jstring xmlFile,
        jstring binFile,
        jstring messagesXml) {

    // Convert Java strings to C++ strings
    const char *xml_file = env->GetStringUTFChars(xmlFile, nullptr);
    const char *bin_file = env->GetStringUTFChars(binFile, nullptr);
    const char *messages_xml = env->GetStringUTFChars(messagesXml, nullptr);

    // Load the angle value and messages from the XML file
    xml::document doc = xml::parse_file(messages_xml);
    double angle_value = std::stod(doc.child("root").child("angle").child_value());
    std::vector<std::string> messages;
    for (auto message : doc.child("root").child("messages").children()) {
        messages.push_back(message.child_value());
    }

    std::vector<float> results;

    // Create SYCL queue
    sycl::queue queue(sycl::default_selector{});

    // Determine the appropriate messages for the angle value using OpenVINO and daal4py
    InferenceEngine::Core ie;
    InferenceEngine::CNNNetReader net_reader;
    net_reader.ReadNetwork(xml_file);
    net_reader.ReadWeights(bin_file);
    InferenceEngine::CNNNetwork network = net_reader.getNetwork();

    // Use SYCL buffer for angle tensor
    sycl::buffer<float> angle_buffer(&angle_value, sycl::range<1>(1));

    // Create a command group to perform inference
    queue.submit([&](sycl::handler& cgh) {
        // Get access to the buffer
        auto angle_acc = angle_buffer.get_access<sycl::access::mode::read>(cgh);

        // Determine input and output blobs
        auto input_info = network.getInputsInfo().begin()->second;
        auto output_info = network.getOutputsInfo().begin()->second;
        InferenceEngine::BlobMap inputs;
        inputs[input_info->name()] = InferenceEngine::make_shared_blob<float>({ InferenceEngine::Precision::FP32, {1} }, angle_acc.get_pointer());
        InferenceEngine::OutputsDataMap outputs_info(network.getOutputsInfo());
        auto output_name = outputs_info.begin()->first;
        InferenceEngine::BlobMap output;
        output[output_name] = InferenceEngine::make_shared_blob<float>({ InferenceEngine::Precision::FP32, {1} });

        // Load the network
        auto exec_net = ie.LoadNetwork(network, "CPU");

        // Create a SYCL buffer for the output data
        sycl::buffer<float, 1> output_buffer(output[output_name]->buffer().as<float*>(), sycl::range<1>(1));

        // Run inference
        cgh.parallel_for(sycl::range<1>(1), [=](sycl::id<1> idx) {
            exec_net.infer(inputs, output);
            output_buffer[idx] = output[output_name]->buffer().template as<float*>()[idx];
        });
    });

    // Wait for the computation to finish
    queue.wait();

    // Get the output results from the buffer
    auto output_accessor = output_buffer.template get_access<sycl::access::mode::read>(cgh, sycl::range<1>(1), sycl::id<1>(0));
        
        // Store the result in the results vector
        results.push_back(output_accessor[0]);
    });

    // Release the Java strings
    env->ReleaseStringUTFChars(xmlFile, xml_file);
    env->ReleaseStringUTFChars(binFile, bin_file);
    env->ReleaseStringUTFChars(messagesXml, messages_xml);

    // Convert the results to a Java object array
    jclass floatClass = env->FindClass("java/lang/Float");
    jmethodID floatConstructor = env->GetMethodID(floatClass, "<init>", "(F)V");

    jobjectArray resultArray = env->NewObjectArray(results.size(), floatClass, nullptr);
    for (size_t i = 0; i < results.size(); i++) {
        jfloat result = static_cast<jfloat>(results[i]);
        jobject floatObj = env->NewObject(floatClass, floatConstructor, result);
        env->SetObjectArrayElement(resultArray, i, floatObj);
        env->DeleteLocalRef(floatObj);
    }

    return resultArray;
}

