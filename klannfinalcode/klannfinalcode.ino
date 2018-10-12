//4 - 141  
//3 - 126  
//2 - 150  = 1.45
//1 - 155  = 1.23

// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  int Speed=120;
  // turn on motor
  motor1.setSpeed(90);
  motor1.run(RELEASE);
  motor2.setSpeed(120);  
  motor2.run(RELEASE);
  motor3.setSpeed(230);
  motor3.run(RELEASE);
  motor4.setSpeed(200);
  motor4.run(RELEASE);

}

void loop() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);

}
