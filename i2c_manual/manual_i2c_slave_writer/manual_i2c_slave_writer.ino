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


typedef struct vector {
  double Direction;
  int Magnitude;
};

struct vector Vector;

double vector_direction(uint8_t);
int vector_magnitude(uint8_t);

int* calc_motor_speeds(int v, double theta);

void setup ()
{
  
  Serial.begin(115200);
  Wire.begin(8);
  Wire.onRequest(requestEvent);

  if (Usb.Init() == -1)
  {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
}

void loop ()
{
    
}

void requestEvent()
{
  do {
    Usb.Task();
    
    if (Xbox.XboxReceiverConnected) {
      for (uint8_t i = 0; i < 4; i++) {
        if (Xbox.Xbox360Connected[i]) {
          xboxNumber =  i;
      
          Vector.Direction = vector_direction( xboxNumber);  //GET VECTOR DIRECTION
          Vector.Magnitude = vector_magnitude( xboxNumber); //GET VECTOR MAGNITUDE

          if (Xbox.getButtonPress(B,  xboxNumber)) {   
           Wire.write(1);
           Serial.println("hard_brake");
          }

          else if (Xbox.getButtonPress(A,  xboxNumber)) {
            Wire.write(2);
            Serial.println("soft_brake");
          }
          else if (Xbox.getButtonPress(R1,  xboxNumber)) {
            Wire.write(3);
            Serial.println("Clock");
           // fheading = 1;
          }
          else if (Xbox.getButtonPress(L1,  xboxNumber)) {
            Wire.write(4);
            Serial.println("Anticlock");
           // fheading = 1;
          }
          else if ((Xbox.getAnalogHat(LeftHatX,  xboxNumber) > 12000 || Xbox.getAnalogHat(LeftHatY,  xboxNumber) > 12000 || Xbox.getAnalogHat(LeftHatX,  xboxNumber) < -12000 || Xbox.getAnalogHat(LeftHatY,  xboxNumber) < -12000) && (Xbox.getButtonPress(R2,  xboxNumber)>0))
          {
            
            Vector.Direction = vector_direction( xboxNumber);  //GET VECTOR DIRECTION
            Vector.Magnitude = vector_magnitude( xboxNumber); //GET VECTOR MAGNITUDE
//            int *arr, *motor_speed;
//            char *dir ;
//            int *theta;
//            
//         //   if (fheading == 1)
//            {
//              refrenceheading_ = refrenceheading(mx, my);
//              Serial.println("refrance taken as");
//              Serial.println(refrenceheading_);
//              fheading++;
//            }
//
//            lsm_heading = printHeading(mx, my, refrenceheading_);
//           
//            dir = calc_motor_direction(Vector.Direction);
//            
//            double error = errorcal( lsm_heading, Vector.Direction);
//            motor_speed = calc_motor_speeds(Vector.Magnitude, Vector.Direction); // done
//            set_motor_values(motor_speed, dir);
//            debug_serial_output(motor_speed, dir, Vector.Direction , lsm_heading, error );
          }
          else
          {
//            soft_brake();
            Serial.println("soft_brake");
          }
        }
      }
    }
  }   while (Xbox.Xbox360Connected[xboxNumber]);
//  soft_brake();
  
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
  //  double threshold = 12000;
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
