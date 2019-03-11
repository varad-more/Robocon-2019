
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "MegunoLink.h"
#include "SimpleKalmanFilter.h"

MPU6050 accelgyro(0x69); // <-- use for AD0 high


int16_t ax, ay, az;
int16_t gx, gy, gz;


int mpu [2][2] = {{40, 41}, {42, 43}};

void setup() {
  // put your setup code here, to run once:

  Wire.begin();
  Serial.begin(115200);
  for (int i = 40; i < 44; i++)
  {
   pinMode(i,OUTPUT);
   digitalWrite(i,LOW);
  }
  digitalWrite(40, HIGH);
  digitalWrite(41, LOW);
  digitalWrite(42, LOW);
  digitalWrite(43, LOW);
  Serial.print("l1l1        ");
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  digitalWrite(41, HIGH);
  digitalWrite(40, LOW);
  digitalWrite(42, LOW);
  digitalWrite(43, LOW);
  Serial.println("l1l2     ");
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  digitalWrite(42, HIGH);
  digitalWrite(41, LOW);
  digitalWrite(40, LOW);
  digitalWrite(43, LOW);
  Serial.print("l2l1    ");
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  accelgyro.initialize();
  digitalWrite(43, HIGH);
  digitalWrite(41, LOW);
  digitalWrite(42, LOW);
  digitalWrite(40, LOW);
  Serial.print("l2l2    ");
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
  // put your main code here, to run repeatedly:

}
