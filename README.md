### IntelOneApi-Hackathon
# Intel OneApi Hackathon- Team "Tech Squad"-Mhealth App with Smart Belt For Spinal Diseases
#### The Intel OneAPI hackathon is a programming contest that tests programmers' ability to design original solutions utilizing the OneAPI platform. OneAPI is a unified programming style that enables programmers to create code that effectively executes on many hardware platforms, such as CPUs, GPUs, and FPGAs.The OneAPI platform, which offers tools, libraries, and APIs for creating high-performance, cross-architecture apps, will be made available to hackathon participants. They will get the chance to work on a variety of projects, from developing new apps from scratch to optimizing already existing ones.The hackathon may be available to individuals or teams and is often run by Intel or in partnership with a partner organization. Typically, the participants are given a certain period of time—a weekend or a week, for example—to create their answers and submit them for evaluation.

### Team Tech Squad

####Madupu Srilekha

### Theme

####Healthcare for Undeserved Communities

Underserved communities often face numerous barriers in accessing quality healthcare, including limited infrastructure, lack of medical resources, and geographic isolation. Recognizing these challenges, our team set out to develop an innovative solution that leveraged oneAPI technologies to empower individuals in underserved communities with improved healthcare services.

![image](https://user-images.githubusercontent.com/113164986/236612911-a2bae968-1b7d-4bba-98de-138fd7bd7916.png)




### TOPIC: Mhealth app with SmartBelt (Intel One-API Tools) For spinal problems

We have created a Wearable belt ,allowing for real-time monitoring of the patient's spinal activity and motions. An Android or iOS app will be used to gather, analyze, and send this data to the patient, the doctor, and any relevant family members. It displays details about the bend angle, strain, and pressure applied. provide specific stretching and exercise routines to improve and treat their ailment. By consistently keeping an eye on things and giving feedback, we can help stop the spine from suffering more harm while also promoting healing and recovery.If the patient has been dealing with significant pain and movement abnormalities, the devices implanted inside the belt can transfer vibrations or electric impulses to the spines. it functions as treatment.

#### [Medium Blog Link of Our Project ](https://medium.com/@srilekhamadupu2002/mhealth-app-for-undeserved-communities-mainly-for-spinal-cord-issues-4614de2e50b2)


![image](https://user-images.githubusercontent.com/113164986/236612968-47613908-3edb-47e0-9e69-865aff54c91d.png)


### Technologies Used:

![image](https://user-images.githubusercontent.com/113164986/236613018-799c351f-878e-4346-8ecd-52fb89197d22.png)



#### 1) RASPBERRY PI
#### 2) INTEL ONEAPI TOOLKITS(Math kernel library,AI analytics toolkit,and Basic Python toolkit)
#### 3) Math kernel library- Mathematical Calculations for average values of the sensor
#### 4) AI analytics toolkit- For Data Analysis and Finding the Accurate rate of movements and remedies
#### 5) Use daal4py to improve accuracy and performance of message classification
#### 6) Use SYCL library

##### //Towards Advanced Level we have to use-Intel® oneAPI Deep Neural Networks Library & Intel® oneAPI Collective Communications Library

![image](https://user-images.githubusercontent.com/113164986/236613119-363b5c89-5d2a-428d-b332-7652626a94a6.png)


#### The solution for the problem has been found and we have made teh protoype,Now if we take it to advanced stages the application will be numerous
![image](https://user-images.githubusercontent.com/113662146/226716356-f075e7fc-b801-4608-8f60-b41ea8ed434d.png)

#### The statistics representing the need for the project in a picture
![image](https://user-images.githubusercontent.com/113662146/226716649-837d2930-4768-4095-b1c6-9bbff09613ae.png)


## Steps to Follow:

#### 1)Connect flex Sensor to Raspberry Pi Using an extension Board attached to raspberry Pi(With proper circuits) 
 
#### 2)Install Pyserial Library using the following command
![image](https://user-images.githubusercontent.com/113662146/226814998-9476c6da-e1a9-47ea-bd54-fbddf19ba34c.png)

#### 3)Paste This code snippet(LOGIC) in the raspberry Pi environment that You are running
Full code to be accessed in Github Repositry

while True:
     
    
    GPIO.output(18, GPIO.HIGH)
    time.sleep(0.000002)
    GPIO.output(18, GPIO.LOW)
    while GPIO.input(24) == GPIO.LOW:
        pass
    start = time.time()
    while GPIO.input(24) == GPIO.HIGH:
        pass
    end = time.time()
    duration = end - start
    analog = duration * 1000000 / 58.0
    # Send  value  Android 
    ser.write(str(analoge).encode('utf-8'))
    
 #### 4)create a SPP on Android device.
 ```
    Mac address
    rfcomm0 SerialPort for communication
    
    ![image](https://user-images.githubusercontent.com/113662146/226815983-6c3df99b-0bb9-4976-8c11-8dbe872c901a.png)
```
#### 5)connection establishment on android device:

 ![image](https://user-images.githubusercontent.com/113662146/226824961-aaaf6b1a-b509-4631-8598-4c85c9effe86.png)
 //Import The IO package and UUID package to remove error

### 6)Now Intel One API PART and Android Application 

#### Use of math kernal Library.
```
from intel_math import atan2
import math

angle = atan2(sensor_reading, 1000)
angle_deg = math.degrees(angle)
```
### use Of AI analytical Tool.

import xml.etree.ElementTree as ET
tree = ET.parse('angle.xml')
root = tree.getroot()
angle_value = float
#### Import  Required libraries.

```
import xml.etree.ElementTree as ET
from openvino.inference_engine import IECore
from daal4py import svd, pca
import numpy as np

tree = ET.parse('angles.xml')
root = tree.getroot()
angle_value = float(root.find('angle').text)
messages = [elem.text for elem in root.findall('messages/message')]
```
#### Determine the appropriate messages for the angle value using SYCL.


#### Now to print the messages in android app.


Compile the C++ code of the SYCL library using the Android NDK.
-Documentation for thee above
https://developer.android.com/ndk/guides/
-Create a JNI wrapper class in your Android app that defines the native methods you want to call from your Java code.


## Conclusion

#### In conclusion, a notable advancement in healthcare technology can be seen in the smart belt technology, which combines IntelOneApi IoT and  Intel OneAPi AI analytics to monitor spinal activity, communicate data to an Android app, and deliver therapy through vibrations and impulses The smart belt can offer insights on a person's posture and movements, which might affect their general health and wellness, by tracking spinal activity. The use of IoT technology also makes it possible for data to be collected and transmitted in an efficient manner to an Android app, where it may be remotely examined by medical specialists or the wearer themselves. A useful addition to the smart belt's capabilities is its capacity to deliver treatment through vibrations and impulses. This feature can help users achieve better overall health outcomes by supporting muscle training and rehabilitation.

#### In general, smart belt technology has the ability to enhance people's health and wellbeing by encouraging good behaviors and offering insightful data about how the body works. We may anticipate major gains in patient quality of life and healthcare outcomes as a result of ongoing technological breakthroughs.By boosting the efficiency of AI analytics and expanding the smart belt's processing power, the integration of Intel One API adds a new layer of capability.


## Output Screens

![sample 1 iot](https://user-images.githubusercontent.com/113662146/226892845-5def573f-55d5-4b9c-9310-a3783314b8b5.jpg)
![sample iot 2](https://user-images.githubusercontent.com/113662146/226892817-9cbad78b-10ff-4964-bd87-98f2cc4a6cbf.jpg)
 
 #hardware
 
 ![image](https://user-images.githubusercontent.com/113164986/236613332-54e3ab6e-29a2-4fa6-98f0-d002c96bbe34.png)

![image](https://user-images.githubusercontent.com/113164986/236613262-aca525f6-5013-4417-a593-a156148b98e2.png)


### OutPut Video
https://user-images.githubusercontent.com/113662146/226954722-c03ed411-ae9f-40d9-b21f-5ad26446a6bf.mp4


### Why the theme is opt to the prototype I developed

mHealth app integrated with smart belts offer underserved communities a means to access health education and personalized exercise guidance for managing spinal diseases.These app provide remote monitoring capabilities, allowing individuals to securely transmit their spinal data to healthcare professionals for assessment and guidance.By leveraging wearable technology and sensors in smart belt, users can track their spinal alignment, posture, and movement patterns, empowering them to detect abnormalities or changes in their condition.The data collected from smart belt can be analyzed using machine learning algorithm to provide data-driven insights and predictive suggestions for preventive measures or interventions.Overall, the combination of mHealth app and smart belt has the potential to revolutionize spinal disease management in underserved communities, improving access to healthcare, promoting self-management, and facilitating informed decision-making by healthcare professionals.








