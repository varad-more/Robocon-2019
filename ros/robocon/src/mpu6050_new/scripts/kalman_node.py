#!/usr/bin/env python
import rospy
import numpy as np
from mpu6050_new.msg import accl_values
from mpu6050_new.msg import kalman_values

dt = 8.0/60
F = np.array([[1, dt, 0], [0, 1, dt], [0, 0, 1]])
H = np.array([1, 0, 0]).reshape(1, 3)
Q = np.array([[0.05, 0.05, 0.0], [0.05, 0.05, 0.0], [0.0, 0.0, 0.0]])
R = np.array([0.5]).reshape(1, 1)

class KalmanFilter(object):
    def __init__(self, F = None, B = None, H = None, Q = None, R = None, P = None, x0 = None):

        if(F is None or H is None):
            raise ValueError("Set proper system dynamics.")

        self.n = F.shape[1]
        self.m = H.shape[1]
        self.F = F
        self.H = H
        self.B = 0 if B is None else B
        self.Q = np.eye(self.n) if Q is None else Q
        self.R = np.eye(self.n) if R is None else R
        self.P = np.eye(self.n) if P is None else P
        self.x = np.zeros((self.n, 1)) if x0 is None else x0

    def predict(self, u = 0):
        self.x = np.dot(self.F, self.x) + np.dot(self.B, u)
        self.P = np.dot(np.dot(self.F, self.P), self.F.T) + self.Q
        return self.x

    def update(self, z):
        y = z - np.dot(self.H, self.x)
        S = self.R + np.dot(self.H, np.dot(self.P, self.H.T))
        K = np.dot(np.dot(self.P, self.H.T), np.linalg.inv(S))
        self.x = self.x + np.dot(K, y)
        I = np.eye(self.n)
        self.P = np.dot(np.dot(I - np.dot(K, self.H), self.P), 
        	(I - np.dot(K, self.H)).T) + np.dot(np.dot(K, self.R), K.T)
kf_ax=[]
kf_ay=[]
kf_az=[]
for i in range(0,8,1):
    kf_ax.append(KalmanFilter(F = F, H = H, Q = Q, R = R))
    kf_ay.append(KalmanFilter(F = F, H = H, Q = Q, R = R))
    kf_az.append(KalmanFilter(F = F, H = H, Q = Q, R = R))
    
def callback(mpu):

    msg.mpu_no=mpu.mpu_no
    msg.ax=np.dot(H,kf_ax[mpu.mpu_no].predict())[0]
    msg.ay=np.dot(H,kf_ay[mpu.mpu_no].predict())[0]
    msg.az=np.dot(H,kf_az[mpu.mpu_no].predict())[0]
    kf_ax[mpu.mpu_no].update(mpu.ax)
    kf_ay[mpu.mpu_no].update(mpu.ay)
    kf_az[mpu.mpu_no].update(mpu.az)
    pub.publish(msg)
    
    
def listener():
    rospy.init_node('kalman_node', anonymous=True)
    rospy.Subscriber('mpu_accl_values',accl_values, callback)
    rospy.loginfo("kalman filter started")
    rospy.spin()

if __name__ == '__main__':
    msg = kalman_values()
    pub = rospy.Publisher('kalman_values',kalman_values ,queue_size=60)
    listener()
    
