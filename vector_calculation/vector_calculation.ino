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
void motors_left(char *);
void motors_left(char *, char *);
void motors_right(char *);
void motors_right(char *, char *);
//void locomotion(double, int);

typedef struct vector {
  double Direction;
  int Magnitude;
};

typedef struct motor {
  int p1;
  int p2;
  int pwm;
  char HS = 'x';
};

struct vector Vector;
struct motor M_1, M_2, M_3;

double vector_direction(uint8_t);
int vector_magnitude(uint8_t);

void setup() {

  M_1.pwm = 5;
  M_2.pwm = 6;
  M_3.pwm = 7;
  M_1.p1 = 40;
  M_1.p2 = 41;
  M_2.p1 = 42;
  M_2.p2 = 43;
  M_3.p1 = 44;
  M_3.p2 = 45;

  Serial.begin(115200);
  pinMode(M_1.p1, OUTPUT);
  pinMode(M_1.p2, OUTPUT);
  pinMode(M_2.p1, OUTPUT);
  pinMode(M_2.p2, OUTPUT);
  pinMode(M_3.p1, OUTPUT);
  pinMode(M_3.p2, OUTPUT);

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


        //CLOCKWISE
        if (Xbox.getButtonPress(R1, i)) {
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
            
          }
          else if (Vector.Direction > 25.5 && Vector.Direction < 67.5) {
            Serial.println("forward right");
          }
          else if (Vector.Direction > 67.5 && Vector.Direction < 112.5) {
//            Serial.println("forward")
            motors_left(&M_2.HS,&M_3.HS);
            motors_right(&M_1.HS);
            Serial.print(M_1.HS);
            Serial.print(M_2.HS);
            Serial.println(M_3.HS);
          }
          else if (Vector.Direction > 112.5 && Vector.Direction < 157.5) {
            Serial.println("forward left");
          }
          else if (Vector.Direction > 157.5 && Vector.Direction < 202.5) {
            Serial.println("left");
          }
          else if (Vector.Direction > 202.5 && Vector.Direction < 247.5) {
            Serial.println("backward left");
          }
          else if (Vector.Direction > 247.5 && Vector.Direction < 292.5) {
            Serial.println("backward");
          }
          else if (Vector.Direction > 292.5 && Vector.Direction < 337.5) {
            Serial.println("backward right");
          }


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
  analogWrite(M_1.pwm, 35);
  analogWrite(M_2.pwm, 35);
  analogWrite(M_3.pwm, 35);
}

void motors_left(char *motor) {
  motor = "L";
}
void motors_left(char *motor_l, char *motor_r) {
  *motor_l = "L";
  *motor_r = "L";
}
void motors_right(char *motor) {
  *motor = "R";
}
void motors_right(char *motor_l, char *motor_r) {
  motor_l = "R";
  motor_r = "R";
}
