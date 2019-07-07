#!/usr/bin/env python
from mpu6050_new.srv import *
import rospy
from mpu6050 import MPU6050
from mpu6050_new.msg import accl_values
prev_ax=[0,0,0,0,0,0,0,0]
prev_ay=[0,0,0,0,0,0,0,0]
prev_az=[0,0,0,0,0,0,0,0]

def mpu(req):
    try:
       sensor = MPU6050(0x69)
    except:
      rospy.logerr("error initializing mpu no %d",req.no)
      rospy.logerr("sending previous values")
      return mpu_valuesResponse(prev_ax[req.no],prev_ay[req.no],prev_az[req.no])
    accl = sensor.get_accel_data()
    rospy.loginfo(accl)
    msg.mpu_no=req.no
    msg.ax=prev_ax[req.no]=accl['x']
    msg.ay=prev_ay[req.no]=accl['y']
    msg.az=prev_az[req.no]=accl['z']
    pub.publish(msg)
    return mpu_valuesResponse(accl['x'],accl['y'],accl['z'])

def mpu_server():
    rospy.init_node('mpu_server',log_level=rospy.ERROR)
    rospy.loginfo("service started")
    s = rospy.Service('mpu_data',mpu_values, mpu)
    rospy.spin()

if __name__ == "__main__":
    pub = rospy.Publisher('mpu_accl_values', accl_values,queue_size=10)
    msg = accl_values()
    mpu_server()
