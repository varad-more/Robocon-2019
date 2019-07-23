// Generated by gencpp from file mpu6050_new/mpu_values.msg
// DO NOT EDIT!


#ifndef MPU6050_NEW_MESSAGE_MPU_VALUES_H
#define MPU6050_NEW_MESSAGE_MPU_VALUES_H

#include <ros/service_traits.h>


#include <mpu6050_new/mpu_valuesRequest.h>
#include <mpu6050_new/mpu_valuesResponse.h>


namespace mpu6050_new
{

struct mpu_values
{

typedef mpu_valuesRequest Request;
typedef mpu_valuesResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct mpu_values
} // namespace mpu6050_new


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::mpu6050_new::mpu_values > {
  static const char* value()
  {
    return "9d07d6506a1d6f140e4337bd15bb5dec";
  }

  static const char* value(const ::mpu6050_new::mpu_values&) { return value(); }
};

template<>
struct DataType< ::mpu6050_new::mpu_values > {
  static const char* value()
  {
    return "mpu6050_new/mpu_values";
  }

  static const char* value(const ::mpu6050_new::mpu_values&) { return value(); }
};


// service_traits::MD5Sum< ::mpu6050_new::mpu_valuesRequest> should match 
// service_traits::MD5Sum< ::mpu6050_new::mpu_values > 
template<>
struct MD5Sum< ::mpu6050_new::mpu_valuesRequest>
{
  static const char* value()
  {
    return MD5Sum< ::mpu6050_new::mpu_values >::value();
  }
  static const char* value(const ::mpu6050_new::mpu_valuesRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::mpu6050_new::mpu_valuesRequest> should match 
// service_traits::DataType< ::mpu6050_new::mpu_values > 
template<>
struct DataType< ::mpu6050_new::mpu_valuesRequest>
{
  static const char* value()
  {
    return DataType< ::mpu6050_new::mpu_values >::value();
  }
  static const char* value(const ::mpu6050_new::mpu_valuesRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::mpu6050_new::mpu_valuesResponse> should match 
// service_traits::MD5Sum< ::mpu6050_new::mpu_values > 
template<>
struct MD5Sum< ::mpu6050_new::mpu_valuesResponse>
{
  static const char* value()
  {
    return MD5Sum< ::mpu6050_new::mpu_values >::value();
  }
  static const char* value(const ::mpu6050_new::mpu_valuesResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::mpu6050_new::mpu_valuesResponse> should match 
// service_traits::DataType< ::mpu6050_new::mpu_values > 
template<>
struct DataType< ::mpu6050_new::mpu_valuesResponse>
{
  static const char* value()
  {
    return DataType< ::mpu6050_new::mpu_values >::value();
  }
  static const char* value(const ::mpu6050_new::mpu_valuesResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // MPU6050_NEW_MESSAGE_MPU_VALUES_H