#include <XBOXRECV.h>
#include <math.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXRECV Xbox(&Usb);

int maxSpeed = 100;

struct vector {
  double Direction;
  int Magnitude;
};

struct vector Vector;

double vector_direction(uint8_t);
int vector_magnitude(uint8_t);

void setup() {
  Serial.begin(115200);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
}


void loop() {
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {



        //GET VECTOR DIRECTION
        Vector.Direction = vector_direction(i);
        Serial.print(Vector.Direction);


        Serial.print("\t");

        //GET VECTOR MAGNITUDE
        Vector.Magnitude = vector_magnitude(i);
        Serial.print(Vector.Magnitude);

        Serial.println();


        //ANTICLOCKWISE
        if (Xbox.getButtonPress(L1, i)) {
          Serial.print("anti_clock_wise : ");
          Serial.println(Xbox.getButtonPress(L1, i));
        }

        //CLOCKWISE
        if (Xbox.getButtonPress(R1, i)) {
          Serial.print("clock_wise : ");
          Serial.println(Xbox.getButtonPress(R1, i));
        }
      }
    }
  }
}

double vector_direction(uint8_t i)
{
  double Rx = 0, Ry = 0;
  double angle = 0, dybydx = 0;
  double threshold = 7500;
  Rx = Xbox.getAnalogHat(LeftHatX, i);
  Ry = Xbox.getAnalogHat(LeftHatY, i);
  if (Rx > -threshold && Rx < threshold && Ry > -threshold && Ry < threshold) {
    Serial.print("\tStop\t");
    return 500;     //distinct stop value
  }
  else {
    //  Serial.print(Rx);
    //  Serial.print("\t");
    //  Serial.print(Ry);
    //  Serial.print("\t\t");
    dybydx = (Ry / Rx);
    angle = atan(dybydx);
    if (Rx > 0 && Ry > 0)
    {
      angle = angle  * (180 / PI);
      angle = map(angle, 0, 90, 0, 90);
      //    Serial.print("Angle : ");
      //    Serial.println(angle * (180 / PI));
    }
    else if (Rx < 0 && Ry > 0)
    {
      angle = angle  * (180 / PI);
      angle = map(angle, -90, 0, 90, 180);
      //    Serial.print("Angle : ");
      //    Serial.println(angle);
    }
    else if (Rx < 0 && Ry < 0)
    {

      angle = angle  * (180 / PI);
      angle = map(angle, 0, 90, 180, 270);
      //    Serial.print("Angle : ");
      //    Serial.println(angle);
    }
    else if (Rx > 0 && Ry < 0)
    {

      angle = angle  * (180 / PI);
      angle = map(angle, -90, 0, 270, 360);
      //    Serial.print("Angle : ");
      //    Serial.println(angle);
    }
    return angle;
  }
}

int vector_magnitude(uint8_t i) {
  int magnitude = Xbox.getButtonPress(R2, i);
  magnitude = map(magnitude, 0, 255, 0, maxSpeed);
  return magnitude;
}

