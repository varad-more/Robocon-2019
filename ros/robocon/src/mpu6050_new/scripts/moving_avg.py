#!/usr/bin/env python
import rospy
import numpy as np
from mpu6050_new.msg import kalman_values
from mpu6050_new.msg import mpu_pitch
import math
pitch=np.zeros((8,10),dtype=int)
pointer=np.zeros(8,dtype=int)
avg=np.zeros(8,dtype=int)
def callback(mpu):
    pitch[mpu.mpu_no][pointer[mpu.mpu_no]]=int(math.degrees(math.atan(mpu.ax/math.sqrt(mpu.ay*mpu.ay + mpu.az*mpu.az))))
    pointer[mpu.mpu_no]+=1
    avg[mpu.mpu_no]=np.average(pitch[mpu.mpu_no]) 
    if pointer[mpu.mpu_no]==10 :
        pointer[mpu.mpu_no]=0


if __name__ == "__main__":
    pub = rospy.Publisher('pitch', mpu_pitch,queue_size=60)
    rospy.init_node('moving_avg',log_level=rospy.INFO)
    rospy.Subscriber('kalman_values',kalman_values, callback)
    msg = mpu_pitch()
    n=0
    a=""
    r=rospy.Rate(60)
    while not rospy.is_shutdown():
          msg.mpu_no=n
          msg.pitch=avg[n]
          a=a+"<"+str(n)+":"+str(avg[n])+">"
          n=n+1
          if n==8:
              n=0
             # rospy.loginfo(a)
              a=""
          pub.publish(msg)
          r.sleep() 