# ROBOCON-2019
RULE BOOK - [click on this link to find the Rule Book ]( https://drive.google.com/file/d/18Bg9f_HcFam3VXEZMbYb-xKKC3-llsza/view )

OFFICIAL DOCUMENTATION FOR MR2 - [click on this link to find the Rule Book]
# MR2 

**STRUCTURE**

According to MR2 , making it quadraped makes it different from MR1 and the other bot(s) throughout the history of ROBOCON.


**SENOSORS :**
+ Potentiometer (discarded)
- Inertial Measurement Unit - MPU6050 [click here for the datasheet](https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf)

**SENSOR JUSTIFICATION**
+ Potentiometer

  As in the document , the design of the robot is such that it has 4 legs , so as to measure the angle between two joints we used the potentiometer . As the rotation of pot would be mapped with the range of values. But then due to hysterisis curve which pot generater in anti-clockwise rotation , the idea of using potentiometer was discarded.

- MPU6050 

  So as to replace potentiometer ,idea of MPU6050 was placed. Using the acceleromete which is built-in . Filtering the raw values of the accelerometer with the help of [library](https://github.com/denyssene/SimpleKalmanFilter)  
  
 


  
