#include <XBOXRECV.h>
#include <math.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include <Wire.h>
#include <SFE_LSM9DS0.h>


#define maxSpeed 255

int xboxNumber = 0;

USB Usb;
XBOXRECV Xbox(&Usb);
#define LSM9DS0_XM  0x1D // Would be 0x1E if SDO_XM is LOW
#define LSM9DS0_G   0x6B // Would be 0x6A if SDO_G is LOW

LSM9DS0 dof(MODE_I2C, LSM9DS0_G, LSM9DS0_XM);

#define PRINT_CALCULATED

#define PRINT_SPEED 500 // 500 ms between prints



void clock_wise(int);
void anti_clock_wise(int);
void hard_brake(int);
void soft_brake();
void motors_left(char *);
void motors_left(char *, char *);
void motors_right(char *);
void motors_right(char *, char *);
void forward(int);
void backward(int);
void left(int);
void right(int);
void forward_left(int);
void forward_right(int);
void backward_left(int);
void backward_right(int);

struct vector {
  double Direction;
  int Magnitude;
};

struct motor {
  int p1;
  int p2;
  int pwm;
};

struct vector Vector;
struct motor M_1, M_2, M_3;

double vector_direction(uint8_t);
int vector_magnitude(uint8_t);
double Heading(float , float);

void setup() {
  M_1.pwm = 4;
  M_2.pwm = 2;
  M_3.pwm = 3;
  M_1.p1 = 32;
  M_1.p2 = 30;
  M_2.p1 = 24;
  M_2.p2 = 22;
  M_3.p1 = 28;
  M_3.p2 = 26;

  Serial.begin(115200);
  pinMode(M_1.p1, OUTPUT);
  pinMode(M_1.p2, OUTPUT);
  pinMode(M_2.p1, OUTPUT);
  pinMode(M_2.p2, OUTPUT);
  pinMode(M_3.p1, OUTPUT);
  pinMode(M_3.p2, OUTPUT);

uint16_t status = dof.begin();
Serial.print("LSM9DS0 WHO_AM_I's returned: 0x");
  Serial.println(status, HEX);
  Serial.println("Should be 0x49D4");
  Serial.println();

  hard_brake(255);

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
}

void loop() {float heading ;
  do {
    Usb.Task();
    if (Xbox.XboxReceiverConnected) {
      for (uint8_t i = 0; i < 4; i++) {
        if (Xbox.Xbox360Connected[i]) {
          xboxNumber = i;
          //CLOCKWISE
          if (Xbox.getButtonPress(B, i)) {
            hard_brake(255);
          }
          else if (Xbox.getButtonPress(R1, i)) {
            clock_wise(40);
            Serial.println("Clock");
          }
          //ANTICLOCKWISE
            else if (Xbox.getButtonPress(L1, i)) {
            anti_clock_wise(40);
            Serial.println("Anticlock");
          }
          else if (!Xbox.getButtonPress(L1, i) && !Xbox.getButtonPress(R1, i)) {
            //GET VECTOR DIRECTION
            Vector.Direction = vector_direction(i);
            //          Serial.print(Vector.Direction);
            //          Serial.print("\t");

            //GET VECTOR MAGNITUDE
            Vector.Magnitude = vector_magnitude(i);
            //          Serial.print(Vector.Magnitude);
            //          Serial.println();

            //          locomotion(Vector.Direction, Vector.Magnitude);
            if ((Vector.Direction > 337.5 && Vector.Direction < 360) || (Vector.Direction < 22.5 && Vector.Direction > 0)) {
              Serial.println("right");
              right(Vector.Magnitude);
            }
            else if (Vector.Direction > 25.5 && Vector.Direction < 67.5) {
              Serial.println("forward right");
              forward_right(Vector.Magnitude);
            }
            else if (Vector.Direction > 67.5 && Vector.Direction < 112.5) {
              Serial.println("forward");
              forward(Vector.Magnitude);
            }
            else if (Vector.Direction > 112.5 && Vector.Direction < 157.5) {
              Serial.println("forward left");
              forward_left(Vector.Magnitude);
            }
            else if (Vector.Direction > 157.5 && Vector.Direction < 202.5) {
              Serial.println("left");
              left(Vector.Magnitude);
            }
            else if (Vector.Direction > 202.5 && Vector.Direction < 247.5) {
              Serial.println("backward left");
              backward_left(Vector.Magnitude);
            }
            else if (Vector.Direction > 247.5 && Vector.Direction < 292.5) {
              Serial.println("backward");
              backward(Vector.Magnitude);
            }
            else if (Vector.Direction > 292.5 && Vector.Direction < 337.5) {
              Serial.println("backward right");
              backward_right(Vector.Magnitude);
          }
          heading = Heading(dof.mx,dof.my);
          // Serial.println("")
          }
        }
        //      else {
        //        soft_brake();
        //      }
      }
    }
  }
  while (Xbox.Xbox360Connected[xboxNumber]);
  soft_brake();
}

double vector_direction(uint8_t i)
{
  double Rx = 0, Ry = 0;
  double angle = 0, dybydx = 0;
  double threshold = 12000;
  Rx = Xbox.getAnalogHat(LeftHatX, i);
  Ry = Xbox.getAnalogHat(LeftHatY, i);
  if (Rx > -threshold && Rx < threshold && Ry > -threshold && Ry < threshold)
  {
    soft_brake();
    //    Serial.print("\tStop\t");
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

double Heading(float hx, float hy)
          {
            float heading;

            if (hy > 0)
            {
              heading = 90 - (atan(hx / hy) * (180 / PI));
            }
            else if (hy < 0)
            {
              heading = - (atan(hx / hy) * (180 / PI));
            }
            else // hy = 0
            {
              if (hx < 0) heading = 180;
              else heading = 0;
            }
            //  Serial.print("hx\t");
            //  Serial.print(hx);
            //  Serial.print("\thy\t");
            //  Serial.print(hy);
            if (hx > 0 && hy < 0)
            {
              heading = map(heading, -90, 0, 90, 180);
            }
            else if (hx < 0 && hy < 0)
            {
              heading = map(heading, 0, 90, -90, -180);
            }
            else if (hx < 0 && hy > 0)
            {
              heading = map(heading, -90, 0, 0, -90);
            }
            else if (hx > 0 && hy > 0)
            {
              heading = map(heading, 0, 90, 90, 0);
            }
            Serial.print("\tHeading: ");
            Serial.println(heading);
          return heading ;
          }

int vector_magnitude(uint8_t i) {
  int magnitude = Xbox.getButtonPress(R2, i);
  magnitude = map(magnitude, 0, 255, 0, maxSpeed);
  return magnitude;
}


void clock_wise(int pwm) {
  digitalWrite(M_1.p1, HIGH);
  digitalWrite(M_1.p2, LOW);
  digitalWrite(M_2.p1, LOW);
  digitalWrite(M_2.p2, HIGH);
  digitalWrite(M_3.p1, HIGH);
  digitalWrite(M_3.p2, LOW);
  analogWrite(M_1.pwm, pwm);
  analogWrite(M_2.pwm, pwm);
  analogWrite(M_3.pwm, pwm);
}

void anti_clock_wise(int pwm) {
  digitalWrite(M_1.p1, LOW);
  digitalWrite(M_1.p2, HIGH);
  digitalWrite(M_2.p1, HIGH);
  digitalWrite(M_2.p2, LOW);
  digitalWrite(M_3.p1, LOW);
  digitalWrite(M_3.p2, HIGH);
  analogWrite(M_1.pwm, pwm);
  analogWrite(M_2.pwm, pwm);
  analogWrite(M_3.pwm, pwm);
}

void hard_brake(int intensity) {
  digitalWrite(M_1.p1, HIGH);
  digitalWrite(M_1.p2, HIGH);
  digitalWrite(M_2.p1, HIGH);
  digitalWrite(M_2.p2, HIGH);
  digitalWrite(M_3.p1, HIGH);
  digitalWrite(M_3.p2, HIGH);
  analogWrite(M_1.pwm, intensity);
  analogWrite(M_2.pwm, intensity);
  analogWrite(M_3.pwm, intensity);
}

void soft_brake() {
  digitalWrite(M_1.p1, LOW);
  digitalWrite(M_1.p2, LOW);
  digitalWrite(M_2.p1, LOW);
  digitalWrite(M_2.p2, LOW);
  digitalWrite(M_3.p1, LOW);
  digitalWrite(M_3.p2, LOW);
  analogWrite(M_1.pwm, 200);
  analogWrite(M_2.pwm, 200);
  analogWrite(M_3.pwm, 200);
}

void forward(int pwm)
{
  digitalWrite(M_1.p1, HIGH);
  digitalWrite(M_1.p2, LOW);
  digitalWrite(M_2.p1, LOW);
  digitalWrite(M_2.p2, HIGH);
  digitalWrite(M_3.p1, LOW);
  digitalWrite(M_3.p2, HIGH);
  analogWrite(M_1.pwm, pwm * 0.33);
  analogWrite(M_2.pwm, pwm * 0.33);
  analogWrite(M_3.pwm, pwm * 0.79);
}
void backward(int pwm)
{
  digitalWrite(M_1.p1, LOW);
  digitalWrite(M_1.p2, HIGH);
  digitalWrite(M_2.p1, HIGH);
  digitalWrite(M_2.p2, LOW);
  digitalWrite(M_3.p1, HIGH);
  digitalWrite(M_3.p2, LOW);
  analogWrite(M_1.pwm, pwm * 0.33);
  analogWrite(M_2.pwm, pwm * 0.33);
  analogWrite(M_3.pwm, pwm * 0.54);
}
void left(int pwm)
{
  digitalWrite(M_1.p1, HIGH);
  digitalWrite(M_1.p2, LOW);
  digitalWrite(M_2.p1, HIGH);
  digitalWrite(M_2.p2, LOW);
  digitalWrite(M_3.p1, LOW);
  digitalWrite(M_3.p2, HIGH);
  analogWrite(M_1.pwm, pwm * 0.58);
  analogWrite(M_2.pwm, pwm * 0.38);
  analogWrite(M_3.pwm, pwm * 0);
}
void right(int pwm)
{
  digitalWrite(M_1.p1, LOW);
  digitalWrite(M_1.p2, HIGH);
  digitalWrite(M_2.p1, LOW);
  digitalWrite(M_2.p2, HIGH);
  digitalWrite(M_3.p1, LOW);
  digitalWrite(M_3.p2, HIGH);
  analogWrite(M_1.pwm, pwm * 0.58);
  analogWrite(M_2.pwm, pwm * 0.38);
  analogWrite(M_3.pwm, pwm * 0);
}
void forward_left(int pwm)
{
  digitalWrite(M_1.p1, HIGH);
  digitalWrite(M_1.p2, LOW);
  digitalWrite(M_2.p1, HIGH);
  digitalWrite(M_2.p2, LOW);
  digitalWrite(M_3.p1, LOW);
  digitalWrite(M_3.p2, HIGH);
  analogWrite(M_1.pwm, pwm * 0.91);
  analogWrite(M_2.pwm, pwm * 0.05);
  analogWrite(M_3.pwm, pwm * 0.67);
}
void forward_right(int pwm)
{
  digitalWrite(M_1.p1, LOW);
  digitalWrite(M_1.p2, HIGH);
  digitalWrite(M_2.p1, LOW);
  digitalWrite(M_2.p2, HIGH);
  digitalWrite(M_3.p1, LOW);
  digitalWrite(M_3.p2, HIGH);
  analogWrite(M_1.pwm, pwm * 0.25);
  analogWrite(M_2.pwm, pwm * 0.71);
  analogWrite(M_3.pwm, pwm * 0.67);
}
void backward_left(int pwm)
{
  digitalWrite(M_1.p1, HIGH);
  digitalWrite(M_1.p2, LOW);
  digitalWrite(M_2.p1, HIGH);
  digitalWrite(M_2.p2, LOW);
  digitalWrite(M_3.p1, HIGH);
  digitalWrite(M_3.p2, LOW);
  analogWrite(M_1.pwm, pwm * 0.25);
  analogWrite(M_2.pwm, pwm * 0.71);
  analogWrite(M_3.pwm, pwm * 0.67);
}
void backward_right(int pwm)
{
  digitalWrite(M_1.p1, LOW);
  digitalWrite(M_1.p2, HIGH);
  digitalWrite(M_2.p1, LOW);
  digitalWrite(M_2.p2, HIGH);
  digitalWrite(M_3.p1, HIGH);
  digitalWrite(M_3.p2, LOW);
  analogWrite(M_1.pwm, pwm * 0.91);
  analogWrite(M_2.pwm, pwm * 0.05);
  analogWrite(M_3.pwm, pwm * 0.67);
