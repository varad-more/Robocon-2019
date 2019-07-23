; Auto-generated. Do not edit!


(cl:in-package mpu6050_new-msg)


;//! \htmlinclude kalman_values.msg.html

(cl:defclass <kalman_values> (roslisp-msg-protocol:ros-message)
  ((mpu_no
    :reader mpu_no
    :initarg :mpu_no
    :type cl:fixnum
    :initform 0)
   (ax
    :reader ax
    :initarg :ax
    :type cl:float
    :initform 0.0)
   (ay
    :reader ay
    :initarg :ay
    :type cl:float
    :initform 0.0)
   (az
    :reader az
    :initarg :az
    :type cl:float
    :initform 0.0))
)

(cl:defclass kalman_values (<kalman_values>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <kalman_values>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'kalman_values)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mpu6050_new-msg:<kalman_values> is deprecated: use mpu6050_new-msg:kalman_values instead.")))

(cl:ensure-generic-function 'mpu_no-val :lambda-list '(m))
(cl:defmethod mpu_no-val ((m <kalman_values>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mpu6050_new-msg:mpu_no-val is deprecated.  Use mpu6050_new-msg:mpu_no instead.")
  (mpu_no m))

(cl:ensure-generic-function 'ax-val :lambda-list '(m))
(cl:defmethod ax-val ((m <kalman_values>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mpu6050_new-msg:ax-val is deprecated.  Use mpu6050_new-msg:ax instead.")
  (ax m))

(cl:ensure-generic-function 'ay-val :lambda-list '(m))
(cl:defmethod ay-val ((m <kalman_values>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mpu6050_new-msg:ay-val is deprecated.  Use mpu6050_new-msg:ay instead.")
  (ay m))

(cl:ensure-generic-function 'az-val :lambda-list '(m))
(cl:defmethod az-val ((m <kalman_values>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mpu6050_new-msg:az-val is deprecated.  Use mpu6050_new-msg:az instead.")
  (az m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <kalman_values>) ostream)
  "Serializes a message object of type '<kalman_values>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mpu_no)) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'ax))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'ay))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'az))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <kalman_values>) istream)
  "Deserializes a message object of type '<kalman_values>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'mpu_no)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ax) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'ay) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'az) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<kalman_values>)))
  "Returns string type for a message object of type '<kalman_values>"
  "mpu6050_new/kalman_values")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'kalman_values)))
  "Returns string type for a message object of type 'kalman_values"
  "mpu6050_new/kalman_values")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<kalman_values>)))
  "Returns md5sum for a message object of type '<kalman_values>"
  "b85bc66545609800449b146da1841ce6")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'kalman_values)))
  "Returns md5sum for a message object of type 'kalman_values"
  "b85bc66545609800449b146da1841ce6")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<kalman_values>)))
  "Returns full string definition for message of type '<kalman_values>"
  (cl:format cl:nil "uint8 mpu_no~%float64 ax~%float64 ay~%float64 az~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'kalman_values)))
  "Returns full string definition for message of type 'kalman_values"
  (cl:format cl:nil "uint8 mpu_no~%float64 ax~%float64 ay~%float64 az~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <kalman_values>))
  (cl:+ 0
     1
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <kalman_values>))
  "Converts a ROS message object to a list"
  (cl:list 'kalman_values
    (cl:cons ':mpu_no (mpu_no msg))
    (cl:cons ':ax (ax msg))
    (cl:cons ':ay (ay msg))
    (cl:cons ':az (az msg))
))
