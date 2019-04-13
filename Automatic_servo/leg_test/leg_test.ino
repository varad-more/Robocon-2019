#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "MegunoLink.h"
#include "SimpleKalmanFilter.h"
//#include "utility/twi.h"

MPU6050 accelgyro (0x69);
int e_mea = 1;
float angle;
int e_est = 1;
int q = 1 ;


SimpleKalmanFilter kfx = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx1 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy1 = SimpleKalmanFilter(e_mea, e_est, q);

//Declare constants for mpu
int16_t ax, ay, az;
int16_t gx, gy, gz;
void setup()
{
  Serial.begin(115200);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  Wire.begin();
  digitalWrite(10, HIGH );
  digitalWrite(9, LOW );
  accelgyro.initialize();
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  digitalWrite(10, LOW );
  digitalWrite(9, HIGH );
  accelgyro.initialize();
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  digitalWrite(10, LOW );
  digitalWrite(9, LOW );
}
void loop()
{ //   twi_disable();
  //twi_init();
  digitalWrite(9, HIGH );
  digitalWrite(10, LOW );
  accelgyro.initialize();
  Serial.print(accelgyro.testConnection() ? "MPU6050 9 connection successful" : "MPU6050  9 connection failed");
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  angle = 180 * atan2(ax, az) / PI;
  Serial.print("   "); Serial.print("angle :"); Serial.print(angle);
  digitalWrite(10, HIGH );
  digitalWrite(9, LOW );
  accelgyro.initialize();
  Serial.print(accelgyro.testConnection() ? "MPU6050 10 connection successful" : "MPU6050  10 connection failed");
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  delay(1);
  ax = kfx1.updateEstimate(ax);
  az = kfy1.updateEstimate(az);
  angle = 180 * atan2(ax, az) / PI;
  Serial.print("   "); Serial.print("angle :"); Serial.println(angle);


}
