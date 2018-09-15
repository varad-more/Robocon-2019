#include <XBOXRECV.h>
#include <math.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#define maxSpeed 100

USB Usb;
XBOXRECV Xbox(&Usb);

void clock_wise(int);
void anti_clock_wise(int);
void hard_brake(int);
void soft_brake();
void locomotion(double, int);

struct vector {
  double Direction;
  int Magnitude;
};

struct motor {
  int p1;
  int p2;
  int pwm;
}

struct motor M1;
struct motor M2;
struct motor M3;

#define m1pwm 50
#define m2pwm 30
#define m3pwm 20
M1.p1 40;
M1.p2 41;
M2.p1 42;
M2.p2 43;
M3.p1 44;
M3.p2 45;

struct vector Vector;

double vector_direction(uint8_t);
int vector_magnitude(uint8_t);

void setup() {
  Serial.begin(115200);
  pinMode(m1p1, OUTPUT);
  pinMode(m1p2, OUTPUT);
  pinMode(m2p1, OUTPUT);
  pinMode(m2p2, OUTPUT);
  pinMode(m3p1, OUTPUT);
  pinMode(m3p2, OUTPUT);

  hard_brake(255);

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

        //ANTICLOCKWISE
        if (Xbox.getButtonPress(L1, i)) {
          anti_clock_wise(40);
        }

        //CLOCKWISE
        if (Xbox.getButtonPress(R1, i)) {
          clock_wise(40);
        }

        else {
          //GET VECTOR DIRECTION
          Vector.Direction = vector_direction(i);
          Serial.print(Vector.Direction);
          Serial.print("\t");

          //GET VECTOR MAGNITUDE
          Vector.Magnitude = vector_magnitude(i);
          Serial.print(Vector.Magnitude);
          Serial.println();

          locomotion(Vector.Direction, Vector.Magnitude);

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
  if (Rx > -threshold && Rx < threshold && Ry > -threshold && Ry < threshold)
  {
    soft_brake();
    Serial.print("\tStop\t");
    return 500;     //distinct stop value
  }
  else
  {
    dybydx = (Ry / Rx);
    angle = atan(dybydx);
    if (Rx > 0 && Ry > 0)
    {
      angle = angle  * (180 / PI);
      angle = map(angle, 0, 90, 0, 90);
    }
    else if (Rx < 0 && Ry > 0)
    {
      angle = angle  * (180 / PI);
      angle = map(angle, -90, 0, 90, 180);
    }
    else if (Rx < 0 && Ry < 0)
    {
      angle = angle  * (180 / PI);
      angle = map(angle, 0, 90, 180, 270);
    }
    else if (Rx > 0 && Ry < 0)
    {
      angle = angle  * (180 / PI);
      angle = map(angle, -90, 0, 270, 360);
    }
    return angle;
  }
}

int vector_magnitude(uint8_t i) {
  int magnitude = Xbox.getButtonPress(R2, i);
  magnitude = map(magnitude, 0, 255, 0, maxSpeed);
  return magnitude;
}


void clock_wise(int pwm) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm);
  analogWrite(m3pwm, pwm);
}

void anti_clock_wise(int pwm) {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm);
  analogWrite(m3pwm, pwm);
}

void hard_brake(int intensity) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, intensity);
  analogWrite(m2pwm, intensity);
  analogWrite(m3pwm, intensity);
}

void soft_brake() {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, 35);
  analogWrite(m2pwm, 35);
  analogWrite(m3pwm, 35);
}
