#include "ros/ros.h"
#include <ros/console.h>
#include "mpu6050_new/mpu_values.h"
#include <wiringPi.h>
#include <cstdlib>
#define mpu1  21  
#define mpu2  22  
#define mpu3  23 
#define mpu4  24 
#define mpu5  25    
#define mpu6  26    
#define mpu7  27    
#define mpu8  28    
const int mpu[8]={mpu1,mpu2,mpu3,mpu4,mpu5,mpu6,mpu7,mpu8};
int select_mpu()
{
  static int mpu_no=0;
  if(mpu_no==8) mpu_no=0;
  for(int i=0;i<=7;i++)
  {
    if(i==mpu_no) 
    {
      digitalWrite(mpu[i],HIGH);
      continue;
    }
    digitalWrite(mpu[i],LOW);  
  }
  return mpu_no++;
}
int main(int argc, char **argv)
{
  int mpu_no;
  ros::init(argc, argv, "mpu_client");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<mpu6050_new::mpu_values>("mpu_data");
  ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug);
  mpu6050_new::mpu_values srv;
  wiringPiSetup();
  ros::Rate rate(60);
  for(int i=0;i<=7;i++)
  {
    pinMode (mpu[i], OUTPUT) ; 
    digitalWrite(mpu[i],LOW);
    ROS_DEBUG("mpu no %d - pin no %d",i+1,mpu[i]); 
  }
 ros::service::waitForService("mpu_data", -1);
  ROS_INFO("service found now starting");
  while (ros::ok())
  { 
    mpu_no = select_mpu();
    srv.request.no = mpu_no;
    if (client.call(srv) )
  {
    ROS_DEBUG("mpu =%d ax=%f , ay=%f , az=%f",mpu_no,srv.response.ax,srv.response.ay,srv.response.az);
  }
  else
  {
      ROS_ERROR("no response from mpu =%d",mpu_no);
     
  }
  ros::spinOnce();
  rate.sleep();
  }
  return 0;
}