#!/usr/bin/env python
import rospy
import numpy as np
from mpu6050_new.msg import kalman_values
import math
import serial

pitch=np.zeros(8)
def callback(mpu):
    pitch[mpu.mpu_no]=math.degrees(math.atan(mpu.ax/math.sqrt(mpu.ay*mpu.ay + mpu.az*mpu.az)))
    rospy.logdebug(mpu.mpu_no,pitch[mpu.mpu_no])
    
if __name__ == "__main__":
    rospy.init_node('serial_comm',log_level=rospy.DEBUG)
    rospy.Subscriber('kalman_values',kalman_values, callback)
    ser = serial.Serial('/dev/ttyUSB0')
    ser.baudrate = 9600
    rospy.spin()
    while not rospy.is_shutdown():
        if ser.in_waiting:
             x = ser.read()
             ser.write(str(pitch[x]))

    ser.close() 