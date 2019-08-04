#!/usr/bin/env python
import rospy
import numpy as np
from mpu6050_new.msg import mpu_pitch
import math
import serial
import string
import time
pitch=np.zeros(8,dtype=int)
def callback(mpu):
    pitch[mpu.mpu_no]=mpu.pitch
    rospy.logdebug(pitch[mpu.mpu_no])
    
if __name__ == "__main__":
    rospy.init_node('serial_comm',log_level=rospy.INFO)
    rospy.Subscriber('moving_avg',mpu_pitch, callback)
    connected = False

    while (not connected) and (not rospy.is_shutdown()):
       try:
          ser = serial.Serial('/dev/ttyACM0')
          connected = True
       except :
          rospy.logerr("check ardunio connection!!!!")  
          pass
    rospy.loginfo("connected | starting")
    ser.baudrate = 115200
    r=rospy.Rate(30)
    mpu=0;
    a=""
    while not rospy.is_shutdown():
                  p="{0:d}".format(pitch[mpu])
                  a=a+"<"+str(mpu)+":"+p+">"
                  mpu=mpu+1
                 # rospy.loginfo("H")
                  if mpu==8:
                     rospy.loginfo(a) 
                     a = a.encode() 
                     ser.write(a) 
                     mpu=0
                     a=""
                     ser.flushOutput()
                     ser.flushInput()
                     r.sleep()
                   
 #   print(a)
    ser.close() 
