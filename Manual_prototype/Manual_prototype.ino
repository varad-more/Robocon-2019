#include <XBOXRECV.h>
#include <math.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#define maxSpeed 255

int xboxNumber = 0;

USB Usb;
XBOXRECV Xbox(&Usb);

// pins need to be  redefined

/**/

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

int* calc_motor_speeds(int v, double  theta);
char* calc_motor_direction(double  theta);
void write_motor_dir(int MX_dir_r, int MX_dir_l, char dir);
void set_motor_values(int vel[], char dir[]);
int* debug_serial_input();
//void debug_serial_output (int *vel, char *dir);


void setup() {

  MA.pwm = 5;
  MB.pwm = 6;
  MC.pwm = 7;
  MA.dir_r = 40;
  MA.dir_l = 41;
  MB.dir_r = 42;
  MB.dir_l = 43;
  MC.dir_r = 46;
  MC.dir_l = 47;

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
            //GET VECTOR MAGNITUDE
            Vector.Magnitude = vector_magnitude(i);
          }
        }
        
        int *arr, *motor_speed;
        char *dir ;
        int *theta;
        arr = debug_serial_input();
        motor_speed = calc_motor_speeds(Vector.Magnitude, Vector.Direction); // done
        dir = calc_motor_direction(Vector.Direction);
        set_motor_values(motor_speed , dir);
        
        Serial.print(" ");
        Serial.print(arr[1]);

        //debug_serial_output( calc_motor_speeds(arr[0], arr[1]),  calc_motor_direction(arr[0]));
        Serial.println(arr[0]);
        Serial.println(arr[1]);
        //delay(2000);
      }
    }
  }
  while (Xbox.Xbox360Connected[xboxNumber]);
  soft_brake();
}
int vector_magnitude(uint8_t i) {
  int magnitude = Xbox.getButtonPress(R2, i);
  magnitude = map(magnitude, 0, 255, 0, maxSpeed);
  return magnitude;
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


int* calc_motor_speeds(int v, double  theta)
{
  static int arr[3];
  arr[0] = v * (cos(theta) * 0.866 + sin(theta) * 0.5);
  arr[1] = v * (cos(theta) * 0.866 - sin(theta) * 0.5);
  arr[2] = v * sin(theta);
  return arr;
}

char* calc_motor_direction(int theta)
{
  static char str[4];
  theta = theta - 90;
  if (theta >= 180 && theta < 240)
  {
    str[0] = 'l';
    str[1] = 'r';
    str[2] = 'r';
  }
  else if (theta >= 240 && theta < 300)
  {
    str[0] = 'l';
    str[1] = 'l';
    str[2] = 'r';
  }
  else if (theta >= 300 && theta < 360)
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
  else if (theta >= 120 && theta < 180)
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
  int x, y;  static char vel[10] = {0}, i = 0, theta[10] = {0};
  static int debug_var[2];// debug_var[0]=velocity,debug_var[1]=theta

  while (Serial.available())
  {
    Serial.readBytesUntil(' ', vel, 5);
    Serial.readBytesUntil(' ', theta, 5);
  }
  debug_var[0] = atoi(vel);
  debug_var[1] = atoi(theta);
  return debug_var;
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

void clock_wise(int pwm) {
  digitalWrite(MA.dir_r, HIGH);
  digitalWrite(MA.dir_l, LOW);
  digitalWrite(MB.dir_r, LOW);
  digitalWrite(MB.dir_l, HIGH);
  digitalWrite(MB.dir_r, HIGH);
  digitalWrite(MB.dir_l, LOW);
  analogWrite(MA.pwm, pwm);
  analogWrite(MB.pwm, pwm);
  analogWrite(MC.pwm, pwm);
}

void anti_clock_wise(int pwm) {
  digitalWrite(MA.dir_r, LOW);
  digitalWrite(MA.dir_l, HIGH);
  digitalWrite(MB.dir_r, HIGH);
  digitalWrite(MB.dir_l, LOW);
  digitalWrite(MB.dir_r, LOW);
  digitalWrite(MB.dir_l, HIGH);
  analogWrite(MA.pwm, pwm);
  analogWrite(MB.pwm, pwm);
  analogWrite(MC.pwm, pwm);
}

/*
  void debug_serial_output(int *vel, char *dir )
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
  Serial.println(dir[2]);
  }*/
