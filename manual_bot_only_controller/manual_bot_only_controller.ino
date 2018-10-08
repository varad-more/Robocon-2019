#include <XBOXRECV.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>


int xboxNumber = 0;
#define  maxSpeed 255
USB Usb;
XBOXRECV Xbox(&Usb);

typedef struct vector {
  double Direction;
  int Magnitude;
};

typedef struct motor {
  int dir_r;
  int dir_l;
  int pwm;
};

void clock_wise(int);
void anti_clock_wise(int);

struct vector Vector;
struct motor MA, MB, MC;
double vector_direction(uint8_t);
int vector_magnitude(uint8_t);

void hard_brake(int);
void soft_brake();

int* calc_motor_speeds(int v, int theta);
char* calc_motor_direction(int theta);
void write_motor_dir(int MX_dir_r, int MX_dir_l, char dir);
void set_motor_values(int vel[], char dir[]);
int* debug_serial_input();
void debug_serial_output (int *vel, char *dir,  double theta );

void setup() {

  MA.pwm = 4;
  MB.pwm = 2;
  MC.pwm = 3;
  MA.dir_r = 32;
  MA.dir_l = 30;
  MB.dir_r = 24;
  MB.dir_l = 22;
  MC.dir_r = 28;
  MC.dir_l = 26;

  pinMode(MA.dir_r, OUTPUT);
  pinMode(MA.dir_l, OUTPUT);
  pinMode(MB.dir_r, OUTPUT);
  pinMode(MB.dir_l, OUTPUT);
  pinMode(MC.dir_r, OUTPUT);
  pinMode(MC.dir_l, OUTPUT);
  pinMode(MA.pwm, OUTPUT);
  pinMode(MB.pwm, OUTPUT);
  pinMode(MC.pwm, OUTPUT);
  Serial.begin(9600);

  hard_brake(255);

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
}

void loop() {
  do {
    Usb.Task();
    if (Xbox.XboxReceiverConnected) {
      for (uint8_t i = 0; i < 4; i++) {
        if (Xbox.Xbox360Connected[i]) {
          xboxNumber = i;

          if (Xbox.getButtonPress(B, i)) {
            hard_brake(255);
            Serial.println("hard_brake");
          }

          else if (Xbox.getButtonPress(R1, i)) {
            clock_wise(60);
            Serial.println("Clock"); // clockwise
          }
          else if (Xbox.getButtonPress(L1, i)) {
            anti_clock_wise(60);
            Serial.println("Anticlock"); // anti-clockwise
          }
          else if (!Xbox.getButtonPress(L1, i) && !Xbox.getButtonPress(R1, i) && ( (abs(Xbox.getAnalogHat(LeftHatX, i)) > 0) || abs(Xbox.getAnalogHat(LeftHatY, i)) > 0) && Xbox.getButtonPress(R2, i) > 0 )
          {

            Vector.Direction = vector_direction(i);  //GET VECTOR DIRECTION
            Vector.Magnitude = vector_magnitude(i); //GET VECTOR MAGNITUDE
            int *arr, *motor_speed;
            char *dir ;
            int *theta;
            motor_speed = calc_motor_speeds(Vector.Magnitude, Vector.Direction); // done
            dir = calc_motor_direction(Vector.Direction);
            set_motor_values(motor_speed, dir);
            debug_serial_output(motor_speed, dir, Vector.Direction );
          }
          else
          { soft_brake();
            Serial.println("soft_brake");
          }
        }
      }
    }
  }   while (Xbox.Xbox360Connected[xboxNumber]);
  soft_brake();
}

int vector_magnitude(uint8_t i) {
  int magnitude = Xbox.getButtonPress(R2, i);
  magnitude = map(magnitude, 0, 255, 0, maxSpeed);
  return magnitude;
}

double vector_direction(uint8_t i)
{
  double Rx = 0, Ry = 0;
  double angle = 0, dybydx = 0;
//  double threshold = 12000;
  Rx = Xbox.getAnalogHat(LeftHatX, i);
  Ry = Xbox.getAnalogHat(LeftHatY, i);
                                                  //  if ((Rx > -threshold && Rx < threshold) && (Ry > -threshold && Ry < threshold))
                                                  //  {
                                                  //    soft_brake();
                                                  //    return 500;
//  }
//  else
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

void clock_wise(int pwm) {
  digitalWrite(MA.dir_r, HIGH);
  digitalWrite(MA.dir_l, LOW);
  digitalWrite(MB.dir_r, LOW);
  digitalWrite(MB.dir_l, HIGH);
  digitalWrite(MC.dir_r, HIGH);
  digitalWrite(MC.dir_l, LOW);
  analogWrite(MA.pwm, pwm);
  analogWrite(MB.pwm, pwm);
  analogWrite(MC.pwm, pwm);
}

void anti_clock_wise(int pwm) {
  digitalWrite(MA.dir_r, LOW);
  digitalWrite(MA.dir_l, HIGH);
  digitalWrite(MB.dir_r, HIGH);
  digitalWrite(MB.dir_l, LOW);
  digitalWrite(MC.dir_r, LOW);
  digitalWrite(MC.dir_l, HIGH);
  analogWrite(MA.pwm, pwm);
  analogWrite(MB.pwm, pwm);
  analogWrite(MC.pwm, pwm);
}

void hard_brake(int intensity) {
  digitalWrite(MA.dir_r, HIGH);
  digitalWrite(MA.dir_l, HIGH);
  digitalWrite(MB.dir_r, HIGH);
  digitalWrite(MB.dir_l, HIGH);
  digitalWrite(MC.dir_r, HIGH);
  digitalWrite(MC.dir_l, HIGH);
  analogWrite(MA.pwm, intensity);
  analogWrite(MB.pwm, intensity);
  analogWrite(MC.pwm, intensity);
}

void soft_brake() {
  digitalWrite(MA.dir_r, LOW);
  digitalWrite(MA.dir_l, LOW);
  digitalWrite(MB.dir_r, LOW);
  digitalWrite(MB.dir_l, LOW);
  digitalWrite(MC.dir_r, LOW);
  digitalWrite(MC.dir_l, LOW);
  analogWrite(MA.pwm, 35);
  analogWrite(MB.pwm, 35);
  analogWrite(MC.pwm, 35);
}

int* calc_motor_speeds(int v, int theta)
{
  static int arr[3];
  theta = (float(theta) / 180) * PI;
  arr[0] = v * (cos(theta) * 0.866 + sin(theta) * 0.5);
  arr[1] = v * (cos(theta) * 0.866 - sin(theta) * 0.5);
  arr[2] = v * sin(theta);
  if (arr[0] < 30 && arr[0] > 0)
  {
    arr[0] = 30;
  }
  if (arr[1] < 30  && arr[1] > 0)
  {
    arr[1] = 30;
  }
  if (arr[2] < 30 && arr[2] > 0)
  {
    arr[2] = 30;
  }
  return arr;
}

char* calc_motor_direction(int theta)
{
  static char str[4];
  if (theta >= -180 && theta < -120)
  {
    str[0] = 'l';
    str[1] = 'r';
    str[2] = 'r';
  }
  else if (theta >= -120 && theta < -60)
  {
    str[0] = 'l';
    str[1] = 'l';
    str[2] = 'r';
  }
  else if (theta >= -60 && theta < 0)
  {
    str[0] = 'r';
    str[1] = 'l';
    str[2] = 'r';
  }
  else if (theta >= 0 && theta < 60)
  {
    str[0] = 'r';
    str[1] = 'l';
    str[2] = 'l';
  }
  else if (theta >= 60 && theta < 120)
  {
    str[0] = 'r';
    str[1] = 'r';
    str[2] = 'l';
  }
  else if (theta >= 120 && theta <= 180)
  {
    str[0] = 'l';
    str[1] = 'r';
    str[2] = 'l';
  }
  return str;
}

void write_motor_dir(int MX_dir_r, int MX_dir_l, char dir)
{
  if (dir == 'r' || dir == 'R')
  {
    digitalWrite(MX_dir_r, HIGH);
    digitalWrite(MX_dir_l, LOW);
  }
  else if (dir == 'l' || dir == 'L')
  {
    digitalWrite(MX_dir_r, LOW);
    digitalWrite(MX_dir_l, HIGH);
  }
}

void set_motor_values(int *vel, char *dir)
{
  analogWrite(MA.pwm, vel[0]);
  analogWrite(MB.pwm, vel[1]);
  analogWrite(MC.pwm, vel[2]);
  write_motor_dir(MA.dir_r, MA.dir_l, dir[0]);
  write_motor_dir(MB.dir_r, MB.dir_l, dir[1]);
  write_motor_dir(MC.dir_r, MC.dir_l, dir[2]);
}

int* debug_serial_input()
{
  int x, y;
  static char vel[10] = {0}, i = 0, theta[10] = {0};
  static int debug_var[2];

  while (Serial.available())
  {
    Serial.readBytesUntil(' ', vel, 5);
    Serial.readBytesUntil(' ', theta, 5);
  }
  debug_var[0] = atoi(vel);
  debug_var[1] = atoi(theta);
  return debug_var;
}

void debug_serial_output(int *vel, char *dir , double  theta )
{
  Serial.print(vel[0]);
  Serial.print(" ");
  Serial.print(vel[1]);
  Serial.print(" ");
  Serial.print(vel[2]);
  Serial.print(" ");
  Serial.print(dir[0]);
  Serial.print(" ");
  Serial.print(dir[1]);
  Serial.print(" ");
  Serial.print(dir[2]);
  Serial.print(" ");
  Serial.println(theta);
}
