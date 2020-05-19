#!/usr/bin/env python
import rospy
import numpy as np
from mpu6050_new.msg import kalman_values
import math
import serial
import string
import time
pitch=np.zeros(8,dtype=int)
print(pitch)
def callback(mpu):
    pitch[mpu.mpu_no]=int(math.degrees(math.atan(mpu.ax/math.sqrt(mpu.ay*mpu.ay + mpu.az*mpu.az))))
    rospy.logdebug(pitch[mpu.mpu_no])
    
if __name__ == "__main__":
    rospy.init_node('serial_comm',log_level=rospy.INFO)
    rospy.Subscriber('kalman_values',kalman_values, callback)
    ser = serial.Serial('/dev/ttyACM0')
    ser.baudrate = 115200
    r=rospy.Rate(32)
    mpu=0;
    a='';
    rospy.loginfo("starting")
    while not rospy.is_shutdown():
                   p="{0:d}".format(pitch[mpu])
                   q="<"+str(mpu)+":"+p+">&"
                   a.append(q)
                   mpu+=1;
                   if  mpu==8:
                      a = a.encode()
                      rospy.loginfo("%d %s ",mpu,p)
                      ser.write(a)
                      ser.flushOutput()
                   
                  # if mpu==8: 
                      mpu=0
#                   time.sleep(0.7)
                   r.sleep() 
 #   print(a)
    ser.close() 
