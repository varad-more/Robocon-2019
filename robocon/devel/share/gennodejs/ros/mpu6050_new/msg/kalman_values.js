// Auto-generated. Do not edit!

// (in-package mpu6050_new.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class kalman_values {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.mpu_no = null;
      this.ax = null;
      this.ay = null;
      this.az = null;
    }
    else {
      if (initObj.hasOwnProperty('mpu_no')) {
        this.mpu_no = initObj.mpu_no
      }
      else {
        this.mpu_no = 0;
      }
      if (initObj.hasOwnProperty('ax')) {
        this.ax = initObj.ax
      }
      else {
        this.ax = 0.0;
      }
      if (initObj.hasOwnProperty('ay')) {
        this.ay = initObj.ay
      }
      else {
        this.ay = 0.0;
      }
      if (initObj.hasOwnProperty('az')) {
        this.az = initObj.az
      }
      else {
        this.az = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type kalman_values
    // Serialize message field [mpu_no]
    bufferOffset = _serializer.uint8(obj.mpu_no, buffer, bufferOffset);
    // Serialize message field [ax]
    bufferOffset = _serializer.float64(obj.ax, buffer, bufferOffset);
    // Serialize message field [ay]
    bufferOffset = _serializer.float64(obj.ay, buffer, bufferOffset);
    // Serialize message field [az]
    bufferOffset = _serializer.float64(obj.az, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type kalman_values
    let len;
    let data = new kalman_values(null);
    // Deserialize message field [mpu_no]
    data.mpu_no = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [ax]
    data.ax = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [ay]
    data.ay = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [az]
    data.az = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 25;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mpu6050_new/kalman_values';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b85bc66545609800449b146da1841ce6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 mpu_no
    float64 ax
    float64 ay
    float64 az
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new kalman_values(null);
    if (msg.mpu_no !== undefined) {
      resolved.mpu_no = msg.mpu_no;
    }
    else {
      resolved.mpu_no = 0
    }

    if (msg.ax !== undefined) {
      resolved.ax = msg.ax;
    }
    else {
      resolved.ax = 0.0
    }

    if (msg.ay !== undefined) {
      resolved.ay = msg.ay;
    }
    else {
      resolved.ay = 0.0
    }

    if (msg.az !== undefined) {
      resolved.az = msg.az;
    }
    else {
      resolved.az = 0.0
    }

    return resolved;
    }
};

module.exports = kalman_values;
