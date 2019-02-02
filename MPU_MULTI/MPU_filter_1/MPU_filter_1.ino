#include "I2Cdev.h"
#include "MPU6050.h"


#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif


int16_t ax, ay, az;
int16_t gx, gy, gz;

const int MPU_1 = 8;
const int MPU_2 = 9;
const int MPU_3 = 10;

#define AS 8192.0
#define GS 65.536
const float al = 0.96;
const float dt = 0.04;

#define M_PI 3.14159265359

#define dt 0.01

int16_t* cal_raw_mpu ();

float f_angle = 0 ;

MPU6050 accelgyro(0x69); // <-- use for AD0 high

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


  // configure Arduino LED for
  pinMode(LED_PIN, OUTPUT);
}


void loop() {
  for (int i = 1; i <= 60; i++)
  {
    if (i < 20 )
    {
      digitalWrite(MPU_1, HIGH); digitalWrite(MPU_2, LOW); digitalWrite(MPU_3, LOW);
      mpu_run();
      Serial.print("1 ");
      delay(500);

    }
    else if (i > 20  && i < 40)
    {
      digitalWrite(MPU_1, HIGH); digitalWrite(MPU_2, LOW); digitalWrite(MPU_3, LOW);
      mpu_run();
      Serial.print("2 ");
      delay(500);
    }
    else
    {
      digitalWrite(MPU_1, HIGH); digitalWrite(MPU_2, LOW); digitalWrite(MPU_3, LOW);
      mpu_run();
      Serial.print("3 ");
      delay(500);
    }
  }

}

void mpu_run()
{
  int16_t* raw_values;
  int16_t* filtered_val;

  raw_values = cal_raw_mpu();
  //raw[0]= ax;raw[1]= ay;raw[2]= az;raw[3]= gx;raw[4]= gy;raw[5]= gz;
  Serial.print(raw_values[0]);
  Serial.print(" ");
  Serial.print(raw_values[1]);
  Serial.println();



}

int16_t* cal_raw_mpu ()
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  static int16_t raw [7];

  

             f_angle = al*(ga)+(1-al)*atan2

}
