// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//      2013-05-08 - added multiple output formats
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
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
//MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

int gyro_error=0;                         //We use this variable to only calculate once the gyro data error
//float Gyr_rawX, Gyr_rawY, Gyr_rawZ;     //Here we store the raw data read 
float Gyro_angle_x, Gyro_angle_y;         //Here we store the angle value obtained with Gyro data
float Gyro_raw_error_x, Gyro_raw_error_y; //Here we store the initial gyro data error
int acc_error=0;                         //We use this variable to only calculate once the Acc data error
float rad_to_deg = 180/3.141592654;      //This value is for pasing from radians to degrees values
//float Acc_rawX, Acc_rawY, Acc_rawZ;    //Here we store the raw data read 
float Acc_angle_x, Acc_angle_y;          //Here we store the angle value obtained with Acc data
float Acc_angle_error_x, Acc_angle_error_y; //Here we store the initial Acc data error

float Total_angle_x, Total_angle_y;
float elapsedTime, time, timePrev;   

const int MPU_1 = 8;
const int MPU_2 = 4;
const int MPU_3 = 5;

double gyroangle, gyroAngle, acc, comp_angle,timer;


MPU6050 accelgyro(0x69); // <-- use for AD0 high



// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO

// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO

void mpu_run ();

#define LED_PIN 13
bool blinkState = false;

void setup() {
  pinMode(MPU_1, OUTPUT);
  pinMode(MPU_2, OUTPUT);
  pinMode(MPU_3, OUTPUT);
  digitalWrite(MPU_3, HIGH);
  digitalWrite(MPU_1, HIGH);
  digitalWrite(MPU_2, HIGH);
  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  // initialize serial communication
  // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
  // it's really up to you depending on your project)M
  Serial.begin(38400);

  // initialize device
  Serial.println("Initializing I2C devices...");

  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  // use the code below to change accel/gyro offset values
  /*
    Serial.println("Updating internal sensor offsets...");
    // -76	-2359	1688	0	0	0
    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");
    accelgyro.setXGyroOffset(220);
    accelgyro.setYGyroOffset(76);
    accelgyro.setZGyroOffset(-85);
    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");
  */
   accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    if(acc_error==0)
  {
    for(int a=0; a<200; a++)
    { 
      /*---X---*/
      Acc_angle_error_x = Acc_angle_error_x + ((atan((ay)/sqrt(pow((ax),2) + pow((az),2)))*rad_to_deg));
      /*---Y---*/
      Acc_angle_error_y = Acc_angle_error_y + ((atan(-1*(ax)/sqrt(pow((ay),2) + pow((az),2)))*rad_to_deg)); 
      
      if(a==199)
      {
        Acc_angle_error_x = Acc_angle_error_x/200;
        Acc_angle_error_y = Acc_angle_error_y/200;
        acc_error=1;
      }
    }
  }//end of acc error calculation   

   if(gyro_error==0)
  {
    for(int i=0; i<200; i++)
    {
      /*---X---*/
      Gyro_raw_error_x = Gyro_raw_error_x + (gx/32.8); 
      /*---Y---*/
      Gyro_raw_error_y = Gyro_raw_error_y + (gy/32.8);
      if(i==199)
      {
        Gyro_raw_error_x = Gyro_raw_error_x/200;
        Gyro_raw_error_y = Gyro_raw_error_y/200;
        gyro_error=1;
      }
    }
  }//end of gyro error calculation   
//end of setup void


   
  // configure Arduino LED for
  pinMode(LED_PIN, OUTPUT);
}
void loop() {
//  for (int i = 1; i <= 60; i++)
//  {
//    if (i < 20 )
//    {
//      digitalWrite(MPU_1, HIGH); digitalWrite(MPU_2, LOW); digitalWrite(MPU_3, LOW);
//      mpu_run();
//      Serial.print("1 ");
//      delay(500);
//
//    }
//    else if (i > 20  && i <40)
//    {
//      digitalWrite(MPU_1, LOW); digitalWrite(MPU_2, HIGH); digitalWrite(MPU_3, LOW);
//      mpu_run();
//      Serial.print("2 ");
//      delay(500);
//    }
//    else
//    {
//      digitalWrite(MPU_1, LOW); digitalWrite(MPU_2, LOW); digitalWrite(MPU_3, HIGH);
//      mpu_run();
//      Serial.print("3 ");
//      delay(500);
//    }
//  }
digitalWrite(MPU_1, HIGH); digitalWrite(MPU_2, LOW); digitalWrite(MPU_3, LOW);
mpu_run();

}

void mpu_run()
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  timePrev=time;
  time = millis();
  elapsedTime = (time - timePrev)/1000;
  // read raw accel/gyro measurements from device
  gx = (gx/32.8)-   Gyro_raw_error_x ;
  gy =(gy/32.8)-   Gyro_raw_error_y;

  Gyro_angle_x=gx*elapsedTime;
  Gyro_angle_y=gy*elapsedTime;
   
   Acc_angle_x = (atan((ay)/sqrt(pow((ax),2) + pow((az),2)))*rad_to_deg) - Acc_angle_error_x;
 /*---Y---*/
   Acc_angle_y = (atan(-1*(ax)/sqrt(pow((ay),2) + pow((az),2)))*rad_to_deg) - Acc_angle_error_y;    

    Total_angle_x = 0.98 *(Total_angle_x + Gyro_angle_x) + 0.02*Acc_angle_x;
 /*---Y axis angle---*/
    Total_angle_y = 0.98 *(Total_angle_y + Gyro_angle_y) + 0.02*Acc_angle_y;
   
 Serial.print("Xº: ");
 Serial.print(Total_angle_x);
 Serial.print("   |   ");
 Serial.print("Yº: ");
 Serial.print(Total_angle_y);
 Serial.println(" ");


 
 
  



  // blink LED to indicate activity
  
}
