#include <ros/ros.h>
#include "mpu6050_new/mpu_values.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

using namespace std;

const int I2C_ADDR = 0x68;
const int PWR_MGMT_1 = 0x6B;
float linear_acceleration_x;
float linear_acceleration_y;
float linear_acceleration_z;

float read_word_2c(int fd, int addr) {
  int high = wiringPiI2CReadReg8(fd, addr);
  int low = wiringPiI2CReadReg8(fd, addr+1);
  int val = (high << 8) + low;
  return float((val >= 0x8000) ? -((65535 - val) + 1) : val);
}
bool mpu(mpu6050_new::mpu_values::Request  &req,
         mpu6050_new::mpu_values::Response &res)
         {
           if (req.no==0)
           {
              int fd = wiringPiI2CSetup(I2C_ADDR);
              if (fd == -1) {
                  printf("no i2c device found?\n");
                  return false;
                                   }
                wiringPiI2CWriteReg16(fd, PWR_MGMT_1, 0);
                return true;
           }
           
           ROS_INFO("sending accl");
           res.ax=linear_acceleration_x;
           res.ay=linear_acceleration_y;
           res.az=linear_acceleration_z;
           return true;
         }
int main(int argc, char **argv) {

  // Connect to device.
  int fd = wiringPiI2CSetup(I2C_ADDR);
  ROS_INFO("node started");
  ROS_INFO("fd=%d",fd);
  if (fd == -1) {
    ROS_INFO("no i2c device found?\n");
    return -1;
  }
  // Device starts in sleep mode so wake it up.
  wiringPiI2CWriteReg16(fd, PWR_MGMT_1, 0);

  // Start ROS node stuff.
  ros::init(argc, argv, "mpu6050");
  ros::NodeHandle n;
  ros::ServiceServer service = n.advertiseService("mpu_data", mpu);
  //ros::Rate rate(10);  // hz
  ROS_INFO("entering loop");
  // Publish in loop.
  while(ros::ok()) {
    
    // Read gyroscope values.
    // At default sensitivity of 250deg/s we need to scale by 131.
  //  angular_velocity_x = read_word_2c(fd, 0x43) / 131;
   // angular_velocity_y = read_word_2c(fd, 0x45) / 131;
    // angular_velocity_z = read_word_2c(fd, 0x47) / 131;

    // Read accelerometer values.
    // At default sensitivity of 2g we need to scale by 16384.
    // Note: at "level" x = y = 0 but z = 1 (i.e. gravity)
    // But! Imu msg docs say acceleration should be in m/2 so need to *9.807
    const float la_rescale = 16384.0 / 9.807;
    linear_acceleration_x = read_word_2c(fd, 0x3b) / la_rescale;
    linear_acceleration_y = read_word_2c(fd, 0x3d) / la_rescale;
    linear_acceleration_z = read_word_2c(fd, 0x3f) / la_rescale;  

    ros::spinOnce();
  }
  return 0;
}

