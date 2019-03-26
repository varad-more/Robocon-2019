#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro(0x69);
#define mpu 0 //mpu pin
int16_t ax, ay, az;
int16_t gx, gy, gz;
float angle;

void setup() {
  // put your setup code here, to run once:
  pinMode(mpu, OUTPUT);
  digitalWrite(mpu, HIGH);
  Serial.begin(115200);
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  angle = 180 * atan2(ax, az) / PI;
  Serial.println(angle);
}
