; Auto-generated. Do not edit!


(cl:in-package mpu6050_new-srv)


;//! \htmlinclude mpu_values-request.msg.html

(cl:defclass <mpu_values-request> (roslisp-msg-protocol:ros-message)
  ((no
    :reader no
    :initarg :no
    :type cl:integer
    :initform 0))
)

(cl:defclass mpu_values-request (<mpu_values-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mpu_values-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mpu_values-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mpu6050_new-srv:<mpu_values-request> is deprecated: use mpu6050_new-srv:mpu_values-request instead.")))

(cl:ensure-generic-function 'no-val :lambda-list '(m))
(cl:defmethod no-val ((m <mpu_values-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mpu6050_new-srv:no-val is deprecated.  Use mpu6050_new-srv:no instead.")
  (no m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mpu_values-request>) ostream)
  "Serializes a message object of type '<mpu_values-request>"
  (cl:let* ((signed (cl:slot-value msg 'no)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mpu_values-request>) istream)
  "Deserializes a message object of type '<mpu_values-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'no) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mpu_values-request>)))
  "Returns string type for a service object of type '<mpu_values-request>"
  "mpu6050_new/mpu_valuesRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mpu_values-request)))
  "Returns string type for a service object of type 'mpu_values-request"
  "mpu6050_new/mpu_valuesRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mpu_values-request>)))
  "Returns md5sum for a message object of type '<mpu_values-request>"
  "9d07d6506a1d6f140e4337bd15bb5dec")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mpu_values-request)))
  "Returns md5sum for a message object of type 'mpu_values-request"
  "9d07d6506a1d6f140e4337bd15bb5dec")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mpu_values-request>)))
  "Returns full string definition for message of type '<mpu_values-request>"
  (cl:format cl:nil "int64 no~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mpu_values-request)))
  "Returns full string definition for message of type 'mpu_values-request"
  (cl:format cl:nil "int64 no~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mpu_values-request>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mpu_values-request>))
  "Converts a ROS message object to a list"
  (cl:list 'mpu_values-request
    (cl:cons ':no (no msg))
))
;//! \htmlinclude mpu_values-response.msg.html

(cl:defclass <mpu_values-response> (roslisp-msg-protocol:ros-message)
  ((ax
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

(cl:defclass mpu_values-response (<mpu_values-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <mpu_values-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'mpu_values-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mpu6050_new-srv:<mpu_values-response> is deprecated: use mpu6050_new-srv:mpu_values-response instead.")))

(cl:ensure-generic-function 'ax-val :lambda-list '(m))
(cl:defmethod ax-val ((m <mpu_values-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mpu6050_new-srv:ax-val is deprecated.  Use mpu6050_new-srv:ax instead.")
  (ax m))

(cl:ensure-generic-function 'ay-val :lambda-list '(m))
(cl:defmethod ay-val ((m <mpu_values-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mpu6050_new-srv:ay-val is deprecated.  Use mpu6050_new-srv:ay instead.")
  (ay m))

(cl:ensure-generic-function 'az-val :lambda-list '(m))
(cl:defmethod az-val ((m <mpu_values-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mpu6050_new-srv:az-val is deprecated.  Use mpu6050_new-srv:az instead.")
  (az m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <mpu_values-response>) ostream)
  "Serializes a message object of type '<mpu_values-response>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <mpu_values-response>) istream)
  "Deserializes a message object of type '<mpu_values-response>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<mpu_values-response>)))
  "Returns string type for a service object of type '<mpu_values-response>"
  "mpu6050_new/mpu_valuesResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mpu_values-response)))
  "Returns string type for a service object of type 'mpu_values-response"
  "mpu6050_new/mpu_valuesResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<mpu_values-response>)))
  "Returns md5sum for a message object of type '<mpu_values-response>"
  "9d07d6506a1d6f140e4337bd15bb5dec")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'mpu_values-response)))
  "Returns md5sum for a message object of type 'mpu_values-response"
  "9d07d6506a1d6f140e4337bd15bb5dec")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<mpu_values-response>)))
  "Returns full string definition for message of type '<mpu_values-response>"
  (cl:format cl:nil "float64 ax~%float64 ay~%float64 az~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'mpu_values-response)))
  "Returns full string definition for message of type 'mpu_values-response"
  (cl:format cl:nil "float64 ax~%float64 ay~%float64 az~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <mpu_values-response>))
  (cl:+ 0
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <mpu_values-response>))
  "Converts a ROS message object to a list"
  (cl:list 'mpu_values-response
    (cl:cons ':ax (ax msg))
    (cl:cons ':ay (ay msg))
    (cl:cons ':az (az msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'mpu_values)))
  'mpu_values-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'mpu_values)))
  'mpu_values-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'mpu_values)))
  "Returns string type for a service object of type '<mpu_values>"
  "mpu6050_new/mpu_values")