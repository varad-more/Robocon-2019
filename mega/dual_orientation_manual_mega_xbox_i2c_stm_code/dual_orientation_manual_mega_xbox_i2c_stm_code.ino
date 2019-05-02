#include <XBOXRECV.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include <Wire.h>
#include <avr/wdt.h>
#include <Servo.h>

Servo servo;
int servo_pos = 0;
int xboxNumber = 0;
#define  maxSpeed 255
USB Usb;
XBOXRECV Xbox(&Usb);
String mystring;
String anti_cl, cl, hard_brk, soft_brk, pwm, dir, ori = "0";

struct vector {
  double Direction;
  int Magnitude;
};

#define throw_pin 27
#define lift_pin 29
#define open_pin 23
#define close_pin 25
#define servo_pin 33

//bool throw_pin_state = 1;
//bool lift_pin_state = 1;
//bool open_pin_state = 1;
//bool close_pin_state = 1;

struct vector Vector;
int g, o, l, lag = 0;

double vector_direction(uint8_t);
int vector_magnitude(uint8_t);

int* calc_motor_speeds(int v, double theta);
void requestEvent();

void setup ()
{
  //  wdt_enable(WDTO_8S);
  servo.attach(servo_pin);
  pinMode(throw_pin, OUTPUT);
  pinMode(lift_pin, OUTPUT);
  pinMode(open_pin, OUTPUT);
  pinMode(close_pin, OUTPUT);

  digitalWrite(throw_pin, HIGH);
  digitalWrite(lift_pin, HIGH);
  digitalWrite(open_pin, HIGH);
  digitalWrite(close_pin, HIGH);

  Serial.begin(9600);
  if (Usb.Init() == -1)
  {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
  Wire.begin(8);
  Wire.onRequest(requestEvent);
}

void loop ()
{
  requestXbox();
}

void requestXbox()
{
  //  wdt_reset();
  do {
    Usb.Task();
    if (Xbox.XboxReceiverConnected) {
      for (uint8_t i = 0; i < 4; i++) {
        if (Xbox.Xbox360Connected[i]) {
          xboxNumber =  i;
          //          wdt_reset();
          Vector.Direction = vector_direction( xboxNumber);  //GET VECTOR DIRECTION
          Vector.Magnitude = vector_magnitude( xboxNumber); //GET VECTOR MAGNITUDE

          if (Xbox.getButtonPress(B,  xboxNumber)) {
            hard_brk = String(1);
            Serial.println("hard_brake");
          }

          else if (Xbox.getButtonPress(A,  xboxNumber)) {
            soft_brk = String(1);
            Serial.println("soft_brake");
          }
          else if (Xbox.getButtonPress(R1,  xboxNumber)) {
            cl = String(1);
            Serial.println("Clock");
            // fheading = 1;
          }
          else if (Xbox.getButtonPress(L1,  xboxNumber)) {
            anti_cl = String (1);
            Serial.println("Anticlock");
            // fheading = 1;
          }
          else if ((Xbox.getAnalogHat(LeftHatX,  xboxNumber) > 12000 || Xbox.getAnalogHat(LeftHatY,  xboxNumber) > 12000 || Xbox.getAnalogHat(LeftHatX,  xboxNumber) < -12000 || Xbox.getAnalogHat(LeftHatY,  xboxNumber) < -12000) && (Xbox.getButtonPress(R2,  xboxNumber) > 0))
          {

            Vector.Direction = vector_direction( xboxNumber);  //GET VECTOR DIRECTION
            Vector.Magnitude = vector_magnitude( xboxNumber); //GET VECTOR MAGNITUDE
            pwm = String(int(Vector.Magnitude));
            dir = String(int(Vector.Direction));
            Serial.println(pwm); Serial.print("  "); Serial.print(dir);
          }
          //          if (Xbox.getButtonPress(L2,  xboxNumber) >= 100){
          //        Serial.print(Xbox.getButtonPress(L2,  xboxNumber));
          //            Serial.println("Throw");
          //
        }
        if (Xbox.getButtonPress(R3,  xboxNumber)) {
          servo.write(servo_pos + 180);
          delay(15);
        }
        if (Xbox.getButtonPress(L3,  xboxNumber)) {
          digitalWrite(throw_pin, LOW);
        } else
          digitalWrite(throw_pin, HIGH);

        if (Xbox.getButtonPress(Y ,   xboxNumber)) {
          digitalWrite(lift_pin, LOW);
        } else
          digitalWrite(lift_pin, HIGH);
        if (Xbox.getButtonPress(UP,  xboxNumber)) {

        }
        if (Xbox.getButtonPress(DOWN,  xboxNumber)) {

        }
        if (Xbox.getButtonPress(LEFT,  xboxNumber)) {
          digitalWrite(open_pin, LOW);
        } else
          digitalWrite(open_pin, HIGH);

        if (Xbox.getButtonPress(RIGHT,  xboxNumber)) {
          digitalWrite(close_pin, LOW);
        } else
          digitalWrite(close_pin, HIGH);

        if (Xbox.getButtonPress(START,  xboxNumber)) {
          //single wheel forward
          ori = "0";
        }
        if (Xbox.getButtonPress(BACK,  xboxNumber)) {
          ori = "1";
        }
      }
    }
  }
  while (Xbox.Xbox360Connected[xboxNumber]);
  //  soft_brake();
}
void requestEvent()
{
  mystring = hard_brk + ',' + soft_brk + ',' + cl + ',' + anti_cl + ',' + pwm + ',' + dir + ',' + ori ;
  Serial.println(mystring);
  Wire.write(mystring.c_str());
  hard_brk = "0";
  soft_brk = "0";
  cl = "0";
  anti_cl = "0";
  pwm = "000";
  dir = "0000";
}

int vector_magnitude(uint8_t  xboxNumber)
{
  int magnitude = Xbox.getButtonPress(R2,  xboxNumber);
  magnitude = map(magnitude, 0, 255, 0, maxSpeed);
  return magnitude;
}

double vector_direction(uint8_t  xboxNumber)
{
  double Rx = 0, Ry = 0;
  double angle = 0, dybydx = 0;
  Rx = Xbox.getAnalogHat(LeftHatX,  xboxNumber);
  Ry = Xbox.getAnalogHat(LeftHatY,  xboxNumber);
  {
    dybydx = (Ry / Rx);
    angle = atan(dybydx);
    if (Rx >= 0 && Ry >= 0)
    {
      angle = angle  * (180 / PI);
      angle = map(angle, 0, 90, 90, 0);
    }
    else if (Rx < 0 && Ry >= 0)
    {
      angle = angle  * (180 / PI);
      angle = map(angle, -90, 0, 0, -90);// 90 180
    }
    else if (Rx < 0 && Ry < 0)
    {
      angle = angle  * (180 / PI);
      angle = map(angle, 0, 90, -90, -180);//180 270
    }
    else if (Rx >= 0 && Ry < 0)
    {
      angle = angle  * (180 / PI);
      angle = map(angle, -90, 0, 180, 90);//270 360
    }
    return angle;
  }
}
