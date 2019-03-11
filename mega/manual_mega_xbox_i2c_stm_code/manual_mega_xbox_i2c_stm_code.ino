#include <XBOXRECV.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include <Wire.h>

int xboxNumber = 0;
#define  maxSpeed 255
USB Usb;
XBOXRECV Xbox(&Usb);
String mystring;
String anti_cl,cl,hard_brk,soft_brk,pwm,dir;

struct vector {
  double Direction;
  int Magnitude;
};

struct vector Vector;
int g,o,l,lag=0;

double vector_direction(uint8_t);
int vector_magnitude(uint8_t);

int* calc_motor_speeds(int v, double theta);
//v/oid requestEvent();

void setup ()
{
  pinMode(21,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(27,OUTPUT);
  Serial.begin(115200);
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
  do {
     Usb.Task();
    if (Xbox.XboxReceiverConnected) {
      for (uint8_t i = 0; i < 4; i++) {
        if (Xbox.Xbox360Connected[i]) {
          xboxNumber =  i;
          Vector.Direction = vector_direction( xboxNumber);  //GET VECTOR DIRECTION
          Vector.Magnitude = vector_magnitude( xboxNumber); //GET VECTOR MAGNITUDE
          digitalWrite(21,HIGH);
          digitalWrite(23,HIGH);    
          digitalWrite(25,HIGH);
          digitalWrite(27,HIGH); 
          if (Xbox.getButtonPress(B,  xboxNumber)) {
            hard_brk = String(1);
            Serial.println("hard_brake");
          }

          else if (Xbox.getButtonPress(A,  xboxNumber)) {
            soft_brk = String(1);
            Serial.println("soft_brake");
          }
          else if (Xbox.getButtonPress(R1,  xboxNumber)) {
            cl= String(1);
            Serial.println("Clock");
            // fheading = 1;
          }
          else if (Xbox.getButtonPress(L1,  xboxNumber)) {
            anti_cl= String (1);
            Serial.println("Anticlock");
            // fheading = 1;
          }
          else if ((Xbox.getAnalogHat(LeftHatX,  xboxNumber) > 12000 || Xbox.getAnalogHat(LeftHatY,  xboxNumber) > 12000 || Xbox.getAnalogHat(LeftHatX,  xboxNumber) < -12000 || Xbox.getAnalogHat(LeftHatY,  xboxNumber) < -12000) && (Xbox.getButtonPress(R2,  xboxNumber) > 0))
          {

            Vector.Direction = vector_direction( xboxNumber);  //GET VECTOR DIRECTION
            Vector.Magnitude = vector_magnitude( xboxNumber); //GET VECTOR MAGNITUDE
            pwm = String(int(Vector.Magnitude));
            dir = String(int(Vector.Direction));
          }
          if (Xbox.getButtonPress(L2,  xboxNumber) >= 100){
            Serial.print(Xbox.getButtonPress(L2,  xboxNumber));
            Serial.println("Throw");
          }
          if (Xbox.getButtonPress(X,  xboxNumber)){
                        digitalWrite(21,LOW);

          }
          else if (Xbox.getButtonPress(Y,  xboxNumber)){
            //
          }
          else if (Xbox.getButtonPress(UP,  xboxNumber)){
            //lift
            digitalWrite(23,LOW);
            Serial.println("Lift shagai");
          }
          else if (Xbox.getButtonPress(DOWN,  xboxNumber)){
            //drop
            Serial.println("Drop shagai");
            digitalWrite(25,LOW);
          }
          else if (Xbox.getButtonPress(LEFT,  xboxNumber)){
            //open
            Serial.println("Open");
          }
          else if (Xbox.getButtonPress(RIGHT,  xboxNumber)){
            //close
            Serial.println("Close");
          }
          else if (Xbox.getButtonPress(START,  xboxNumber)){
            //upload mode on stm
          }
          else if (Xbox.getButtonPress(BACK,  xboxNumber)){
            
          }
        }
      }
    }
  }   while (Xbox.Xbox360Connected[xboxNumber]);
  //  soft_brake();
}
void requestEvent()
{
  mystring= hard_brk + ',' + soft_brk + ',' + cl + ',' + anti_cl + ',' + pwm + ',' + dir ;
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
