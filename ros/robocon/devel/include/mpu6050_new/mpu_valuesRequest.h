// Generated by gencpp from file mpu6050_new/mpu_valuesRequest.msg
// DO NOT EDIT!


#ifndef MPU6050_NEW_MESSAGE_MPU_VALUESREQUEST_H
#define MPU6050_NEW_MESSAGE_MPU_VALUESREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace mpu6050_new
{
template <class ContainerAllocator>
struct mpu_valuesRequest_
{
  typedef mpu_valuesRequest_<ContainerAllocator> Type;

  mpu_valuesRequest_()
    : no(0)  {
    }
  mpu_valuesRequest_(const ContainerAllocator& _alloc)
    : no(0)  {
  (void)_alloc;
    }



   typedef int64_t _no_type;
  _no_type no;





  typedef boost::shared_ptr< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> const> ConstPtr;

}; // struct mpu_valuesRequest_

typedef ::mpu6050_new::mpu_valuesRequest_<std::allocator<void> > mpu_valuesRequest;

typedef boost::shared_ptr< ::mpu6050_new::mpu_valuesRequest > mpu_valuesRequestPtr;
typedef boost::shared_ptr< ::mpu6050_new::mpu_valuesRequest const> mpu_valuesRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mpu6050_new

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg'], 'mpu6050_new': ['/home/suraj/robocon/src/mpu6050_new/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "0e823d83996fd54d55a7d05b966f081e";
  }

  static const char* value(const ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x0e823d83996fd54dULL;
  static const uint64_t static_value2 = 0x55a7d05b966f081eULL;
};

template<class ContainerAllocator>
struct DataType< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mpu6050_new/mpu_valuesRequest";
  }

  static const char* value(const ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int64 no\n"
;
  }

  static const char* value(const ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.no);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct mpu_valuesRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mpu6050_new::mpu_valuesRequest_<ContainerAllocator>& v)
  {
    s << indent << "no: ";
    Printer<int64_t>::stream(s, indent + "  ", v.no);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MPU6050_NEW_MESSAGE_MPU_VALUESREQUEST_H