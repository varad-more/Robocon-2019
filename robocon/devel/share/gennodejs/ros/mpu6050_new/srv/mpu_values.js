// Auto-generated. Do not edit!

// (in-package mpu6050_new.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class mpu_valuesRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.no = null;
    }
    else {
      if (initObj.hasOwnProperty('no')) {
        this.no = initObj.no
      }
      else {
        this.no = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type mpu_valuesRequest
    // Serialize message field [no]
    bufferOffset = _serializer.int64(obj.no, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mpu_valuesRequest
    let len;
    let data = new mpu_valuesRequest(null);
    // Deserialize message field [no]
    data.no = _deserializer.int64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'mpu6050_new/mpu_valuesRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0e823d83996fd54d55a7d05b966f081e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int64 no
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new mpu_valuesRequest(null);
    if (msg.no !== undefined) {
      resolved.no = msg.no;
    }
    else {
      resolved.no = 0
    }

    return resolved;
    }
};

class mpu_valuesResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ax = null;
      this.ay = null;
      this.az = null;
    }
    else {
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
    // Serializes a message object of type mpu_valuesResponse
    // Serialize message field [ax]
    bufferOffset = _serializer.float64(obj.ax, buffer, bufferOffset);
    // Serialize message field [ay]
    bufferOffset = _serializer.float64(obj.ay, buffer, bufferOffset);
    // Serialize message field [az]
    bufferOffset = _serializer.float64(obj.az, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type mpu_valuesResponse
    let len;
    let data = new mpu_valuesResponse(null);
    // Deserialize message field [ax]
    data.ax = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [ay]
    data.ay = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [az]
    data.az = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 24;
  }

  static datatype() {
    // Returns string type for a service object
    return 'mpu6050_new/mpu_valuesResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '271a8351f08a1993852d2e5e55f1efa1';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new mpu_valuesResponse(null);
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

module.exports = {
  Request: mpu_valuesRequest,
  Response: mpu_valuesResponse,
  md5sum() { return '9d07d6506a1d6f140e4337bd15bb5dec'; },
  datatype() { return 'mpu6050_new/mpu_values'; }
};
