// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//      2010-05-08 - added multiple output formats
//                 - added seamless Fastwire support
//      2011-10-07 - initial release

/* ============================================
  I2Cdev device library code is placed under the MIT license
  Copyright (c) 2011 Jeff Rowberg

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  ===============================================
*/

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
//#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
//#include "Wire.h"
//#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
//MPU6050 accelgyro;
MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax1, ay1, az1;
int16_t gx1, gy1, gz1;

int16_t ax2, ay2, az2;
int16_t gx2, gy2, gz2;

// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO

// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO

void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  //#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  //  Wire.begin();
  //#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  //  Fastwire::setup(400, true);
  //#endif

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(9, HIGH); digitalWrite(10, HIGH);
  Serial.begin(115200);

  // initialize device
  Serial.println("Initializing I2C devices...");

  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  delay(10);
  //  Serial.print("adhi");
  accelgyro.initialize();
  delay(10);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  // verify connection
  Serial.println("Testing device 1 connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 1 connection successful" : "MPU6050 connection failed");
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  delay(10);
  accelgyro.initialize();
  delay(10);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  // verify connection
  Serial.println("Testing device 2 connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 2 connection successful" : "MPU6050 connection failed");
  delay(2000);
}

void loop() {
  //  delay(500);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  delay(10);
  accelgyro.getMotion6(&ax1, &ay1, &az1, &gx1, &gy1, &gz1);
  delay(10);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);

  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  delay(10);
  accelgyro.getMotion6(&ax2, &ay2, &az2, &gx2, &gy2, &gz2);
  delay(10);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);

#ifdef OUTPUT_READABLE_ACCELGYRO
  // display tab-separated accel/gyro x/y/z values
  Serial.println("a/g:\t\n");
  Serial.print("ax:"); Serial.print(ax1); Serial.print("\t"); Serial.print(ax2); Serial.print("\n");
  Serial.print("ay:"); Serial.print(ay1); Serial.print("\t"); Serial.print(ay2); Serial.print("\n");
  Serial.print("az:"); Serial.print(az1); Serial.print("\t"); Serial.print(az2); Serial.print("\n");
  Serial.print("gx:"); Serial.print(gx1); Serial.print("\t"); Serial.print(gx2); Serial.print("\n");
  Serial.print("gy:"); Serial.print(gy1); Serial.print("\t"); Serial.print(gy2); Serial.print("\n");
  Serial.print("gz:"); Serial.print(gz1); Serial.print("\t"); Serial.print(gz2); Serial.print("\n");
  Serial.println();
#endif
}
