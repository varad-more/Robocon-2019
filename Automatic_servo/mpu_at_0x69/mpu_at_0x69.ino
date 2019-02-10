#include "I2Cdev.h"
#include "MPU6050.h"
#include "MegunoLink.h"
#include "Filter.h"

float angle = 0.0;
// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include "Wire.h"
ExponentialFilter<long> ADCFilter(1, 0);

MPU6050 accelgyro;//(0x69);

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
  // put your main code here, to run repeatedly:
  //  for (int i = 0; i < 10; i++)
  //  {
  //    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  //    angle = 0.98 * (angle + gx * (0.1)) + 0.02 * ax;
  //  }
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ADCFilter.Filter(ay);
  ay = ADCFilter.Current();
  //  delay(100);
  if (az > 0)
  {
    ay = map(ay, 0, -17000, 0, 90);
  } else {
    ay = map(ay, -17000, 0, 90, 180);
  }

  Serial.println(ay);
  //  Serial.print("\t");
  //  Serial.println(az);
  //  delay(100);
}
