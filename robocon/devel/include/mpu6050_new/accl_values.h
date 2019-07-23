// Generated by gencpp from file mpu6050_new/accl_values.msg
// DO NOT EDIT!


#ifndef MPU6050_NEW_MESSAGE_ACCL_VALUES_H
#define MPU6050_NEW_MESSAGE_ACCL_VALUES_H


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
struct accl_values_
{
  typedef accl_values_<ContainerAllocator> Type;

  accl_values_()
    : mpu_no(0)
    , ax(0.0)
    , ay(0.0)
    , az(0.0)  {
    }
  accl_values_(const ContainerAllocator& _alloc)
    : mpu_no(0)
    , ax(0.0)
    , ay(0.0)
    , az(0.0)  {
  (void)_alloc;
    }



   typedef uint8_t _mpu_no_type;
  _mpu_no_type mpu_no;

   typedef double _ax_type;
  _ax_type ax;

   typedef double _ay_type;
  _ay_type ay;

   typedef double _az_type;
  _az_type az;




  typedef boost::shared_ptr< ::mpu6050_new::accl_values_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mpu6050_new::accl_values_<ContainerAllocator> const> ConstPtr;

}; // struct accl_values_

typedef ::mpu6050_new::accl_values_<std::allocator<void> > accl_values;

typedef boost::shared_ptr< ::mpu6050_new::accl_values > accl_valuesPtr;
typedef boost::shared_ptr< ::mpu6050_new::accl_values const> accl_valuesConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mpu6050_new::accl_values_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mpu6050_new::accl_values_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace mpu6050_new

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'mpu6050_new': ['/home/pi/robocon/src/mpu6050_new/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::mpu6050_new::accl_values_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mpu6050_new::accl_values_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mpu6050_new::accl_values_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mpu6050_new::accl_values_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mpu6050_new::accl_values_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mpu6050_new::accl_values_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mpu6050_new::accl_values_<ContainerAllocator> >
{
  static const char* value()
  {
    return "b85bc66545609800449b146da1841ce6";
  }

  static const char* value(const ::mpu6050_new::accl_values_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xb85bc66545609800ULL;
  static const uint64_t static_value2 = 0x449b146da1841ce6ULL;
};

template<class ContainerAllocator>
struct DataType< ::mpu6050_new::accl_values_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mpu6050_new/accl_values";
  }

  static const char* value(const ::mpu6050_new::accl_values_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mpu6050_new::accl_values_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint8 mpu_no\n\
float64 ax\n\
float64 ay\n\
float64 az\n\
";
  }

  static const char* value(const ::mpu6050_new::accl_values_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mpu6050_new::accl_values_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.mpu_no);
      stream.next(m.ax);
      stream.next(m.ay);
      stream.next(m.az);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct accl_values_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mpu6050_new::accl_values_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mpu6050_new::accl_values_<ContainerAllocator>& v)
  {
    s << indent << "mpu_no: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.mpu_no);
    s << indent << "ax: ";
    Printer<double>::stream(s, indent + "  ", v.ax);
    s << indent << "ay: ";
    Printer<double>::stream(s, indent + "  ", v.ay);
    s << indent << "az: ";
    Printer<double>::stream(s, indent + "  ", v.az);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MPU6050_NEW_MESSAGE_ACCL_VALUES_H