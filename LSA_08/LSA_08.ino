#include <AFMotor.h>
AF_DCMotor motor3(3);
AF_DCMotor motor2(2);
const byte analogPin = 4;
const float Kp = 0.142;   // Kp value that you have to change
const int Kd = 4;   // Kd value that you have to change
const int setPoint = 35;    // Middle point of sensor array
const int baseSpeed = 100;    // Base speed for your motors
const int maxSpeed = 200;   // Maximum speed for your motors
int positionVal;
int error=0;
 int motorSpeed,rightMotorSpeed,leftMotorSpeed;
//const byte junctionPulse = 4;   // Connect JPULSE of LSA08 to pin 4


void setup() {
 // pinMode(serialEn,OUTPUT);   // Setting serialEn as digital output pin
  //pinMode(junctionPulse,INPUT);   // Setting junctionPulse as digital input pin
}

int lastError = 0;    // Declare a variable to store previous error

void loop() {
  int positionVal =analogRead(analogPin); 
 // If no line is detected, stay at the position
 if(positionVal>950/*921*/) 
 {motor3.run(RELEASE);
    motor2.run(RELEASE);
 }
  positionVal=map(positionVal,0,830,0,70);
  if(positionVal == setPoint) {
    motor3.setSpeed(200);
    motor2.setSpeed(200);
  }
 

  // Else if line detected, calculate the motor speed and apply
  else {
    error = positionVal - setPoint;   // Calculate the deviation from position to the set point
    motorSpeed = Kp * error + Kd * (error - lastError);   // Applying formula of PID
    lastError = error;    // Store current error as previous error for next iteration use

    // Adjust the motor speed based on calculated value
    // You might need to interchange the + and - sign if your robot move in opposite direction
    rightMotorSpeed = baseSpeed - motorSpeed;
    leftMotorSpeed = baseSpeed + motorSpeed;

    // If the speed of motor exceed max speed, set the speed to max speed
    if(rightMotorSpeed > maxSpeed) rightMotorSpeed = maxSpeed;
    if(leftMotorSpeed > maxSpeed) leftMotorSpeed = maxSpeed;

    // If the speed of motor is negative, set it to 0
    if(rightMotorSpeed < 0) rightMotorSpeed = 0;
    if(leftMotorSpeed < 0) leftMotorSpeed = 0;

    // Writing the motor speed value as output to hardware motor
 motor3.setSpeed(rightMotorSpeed);
  motor2.setSpeed(leftMotorSpeed);
  }

}
