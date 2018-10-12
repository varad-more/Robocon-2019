#include <XBOXRECV.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#include <Wire.h>
#include <SFE_LSM9DS0.h>

#define LSM9DS0_XM  0x1E // Would be 0x1E if SDO_XM is LOW
#define LSM9DS0_G   0x6A // Would be 0x6A if SDO_G is LOW
LSM9DS0 dof(MODE_I2C, LSM9DS0_G, LSM9DS0_XM);

#define GyroMeasError PI * (40.0f / 180.0f)
#define GyroMeasDrift PI * (0.0f / 180.0f)
#define beta sqrt(3.0f / 4.0f) * GyroMeasError
#define zeta sqrt(3.0f / 4.0f) * GyroMeasDrift
#define Kp 2.0f * 5.0f
#define Ki 0.0f

bool flag;
float pitch, yaw, roll, heading;
float deltat = 0.0f;
uint32_t lastUpdate = 0;
uint32_t Now = 0;

float abias[3] = {0, 0, 0}, gbias[3] = {0, 0, 0};
float ax, ay, az, gx, gy, gz, mx, my, mz;
float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};
float eInt[3] = {0.0f, 0.0f, 0.0f};
int fheading = 1;
double  error_calc(double,double);
double refrenceheading_;
double lsm_heading;
double error ;


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
void debug_serial_output (int *vel, char *dir,  double theta , double lsm , double error );
//lsm functions prototypes
double printHeading(float hx, float hy, float refrenceheading_);
void printOrientation(float x, float y, float z);
void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz);
double refrenceheading(float hx, float hy);
double error_calc(double);
void basiclsm();

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

  hard_brake(255);
  Serial.begin(115200);

  uint32_t status = dof.begin();

  Serial.print("LSM9DS0 WHO_AM_I's returned: 0x");
  Serial.println(status, HEX);
  Serial.println("Should be 0x49D4");
  Serial.println();

  dof.setAccelScale(dof.A_SCALE_2G);
  dof.setGyroScale(dof.G_SCALE_245DPS);
  dof.setMagScale(dof.M_SCALE_2GS);
  dof.setAccelODR(dof.A_ODR_200);
  dof.setAccelABW(dof.A_ABW_50);
  dof.setGyroODR(dof.G_ODR_190_BW_125);
  dof.setMagODR(dof.M_ODR_125);
  dof.calLSM9DS0(gbias, abias);

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
}

void loop() {
  do {
    Usb.Task();
    basiclsm();
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
            Serial.println("Clock");
            fheading = 1;
          }
          else if (Xbox.getButtonPress(L1, i)) {
            anti_clock_wise(60);
            Serial.println("Anticlock");
            fheading = 1;
          }
          else if (!Xbox.getButtonPress(L1, i) && !Xbox.getButtonPress(R1, i) && ( (abs(Xbox.getAnalogHat(LeftHatX, i)) > 0) || abs(Xbox.getAnalogHat(LeftHatY, i)) > 0) && abs(Xbox.getButtonPress(R2, i))>0 )
          {

            Vector.Direction = vector_direction(i);  //GET VECTOR DIRECTION
            Vector.Magnitude = vector_magnitude(i); //GET VECTOR MAGNITUDE
            int *arr, *motor_speed;
            char *dir ;
            int *theta;
            if (fheading == 1)
            { 
              refrenceheading_ = refrenceheading(mx, my);
              Serial.println("refrance taken as");
              Serial.println(refrenceheading_);
              fheading++;
            }
            lsm_heading = printHeading(mx, my, refrenceheading_);
            motor_speed = calc_motor_speeds(Vector.Magnitude, Vector.Direction); // done
            dir = calc_motor_direction(Vector.Direction);
            set_motor_values(motor_speed, dir);
            error = error_calc (lsm_heading);    

            debug_serial_output(motor_speed, dir, Vector.Direction , lsm_heading , error);

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

double error_calc(double lsm_heading   )
{
  double set_point, er ;
 if ((lsm_heading> -90 || lsm_heading<90 ) && (Vector.Direction>-90  || Vector.Direction <90))
{
  set_point= Vector.Direction; 
 er = set_point  - lsm_heading ;
  flag = false ; 
}      
 else if ((lsm_heading <-90 || lsm_heading >90) && (Vector.Direction <-90 || Vector.Direction >90))
 {
  double lsm_heading_bX;
  set_point= Vector.Direction-180 ;
 er= set_point- lsm_heading ;
  flag= true ;
 }
 
  return er; 
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

void debug_serial_output(int *vel, char *dir , double  theta , double lsm, double error )
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
  Serial.print(theta);
  Serial.print(" ");
  Serial.print(lsm);
  Serial.print(" ");
  Serial.println(error);
}
void basiclsm()
{
  dof.readGyro();
  gx = dof.calcGyro(dof.gx) - gbias[0];
  gy = dof.calcGyro(dof.gy) - gbias[1];
  gz = dof.calcGyro(dof.gz) - gbias[2];

  dof.readAccel();
  ax = dof.calcAccel(dof.ax) - abias[0];
  ay = dof.calcAccel(dof.ay) - abias[1];
  az = dof.calcAccel(dof.az) - abias[2];

  dof.readMag();
  mx = dof.calcMag(dof.mx);
  my = dof.calcMag(dof.my);
  mz = dof.calcMag(dof.mz);

  Now = micros();
  deltat = ((Now - lastUpdate) / 1000000.0f);
  lastUpdate = Now;
  MadgwickQuaternionUpdate(ax, ay, az, gx * PI / 180.0f, gy * PI / 180.0f, gz * PI / 180.0f, mx, my, mz);
}

//all lsm functions declaration




double refrenceheading(float hx, float hy)
{
  double new_heading ;
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

  if (heading > 0  && heading < 90)

  { if (hy < 0)
    {
      new_heading = heading;
    }

    else
    {
      new_heading = map (heading, 0, 90, 90, 180);
    }
  }
  else if (heading > 90)
  {
    new_heading = map (heading, 90, 180, -180, -90);
  }
  else
  {
    new_heading = heading;
  }
  return new_heading;
}


void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz)
{
  float q1 = q[0], q2 = q[1], q3 = q[2], q4 = q[3];   // short name local variable for readability
  float norm;
  float hx, hy, _2bx, _2bz;
  float s1, s2, s3, s4;
  float qDot1, qDot2, qDot3, qDot4;

  // Auxiliary variables to avoid repeated arithmetic
  float _2q1mx;
  float _2q1my;
  float _2q1mz;
  float _2q2mx;
  float _4bx;
  float _4bz;
  float _2q1 = 2.0f * q1;
  float _2q2 = 2.0f * q2;
  float _2q3 = 2.0f * q3;
  float _2q4 = 2.0f * q4;
  float _2q1q3 = 2.0f * q1 * q3;
  float _2q3q4 = 2.0f * q3 * q4;
  float q1q1 = q1 * q1;
  float q1q2 = q1 * q2;
  float q1q3 = q1 * q3;
  float q1q4 = q1 * q4;
  float q2q2 = q2 * q2;
  float q2q3 = q2 * q3;
  float q2q4 = q2 * q4;
  float q3q3 = q3 * q3;
  float q3q4 = q3 * q4;
  float q4q4 = q4 * q4;

  // Normalise accelerometer measurement
  norm = sqrt(ax * ax + ay * ay + az * az);
  if (norm == 0.0f) return; // handle NaN
  norm = 1.0f / norm;
  ax *= norm;
  ay *= norm;
  az *= norm;

  // Normalise magnetometer measurement
  norm = sqrt(mx * mx + my * my + mz * mz);
  if (norm == 0.0f) return; // handle NaN
  norm = 1.0f / norm;
  mx *= norm;
  my *= norm;
  mz *= norm;

  // Reference direction of Earth's magnetic field
  _2q1mx = 2.0f * q1 * mx;
  _2q1my = 2.0f * q1 * my;
  _2q1mz = 2.0f * q1 * mz;
  _2q2mx = 2.0f * q2 * mx;
  hx = mx * q1q1 - _2q1my * q4 + _2q1mz * q3 + mx * q2q2 + _2q2 * my * q3 + _2q2 * mz * q4 - mx * q3q3 - mx * q4q4;
  hy = _2q1mx * q4 + my * q1q1 - _2q1mz * q2 + _2q2mx * q3 - my * q2q2 + my * q3q3 + _2q3 * mz * q4 - my * q4q4;
  _2bx = sqrt(hx * hx + hy * hy);
  _2bz = -_2q1mx * q3 + _2q1my * q2 + mz * q1q1 + _2q2mx * q4 - mz * q2q2 + _2q3 * my * q4 - mz * q3q3 + mz * q4q4;
  _4bx = 2.0f * _2bx;
  _4bz = 2.0f * _2bz;

  // Gradient decent algorithm corrective step
  s1 = -_2q3 * (2.0f * q2q4 - _2q1q3 - ax) + _2q2 * (2.0f * q1q2 + _2q3q4 - ay) - _2bz * q3 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q4 + _2bz * q2) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q3 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
  s2 = _2q4 * (2.0f * q2q4 - _2q1q3 - ax) + _2q1 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q2 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + _2bz * q4 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q3 + _2bz * q1) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q4 - _4bz * q2) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
  s3 = -_2q1 * (2.0f * q2q4 - _2q1q3 - ax) + _2q4 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q3 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + (-_4bx * q3 - _2bz * q1) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q2 + _2bz * q4) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q1 - _4bz * q3) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
  s4 = _2q2 * (2.0f * q2q4 - _2q1q3 - ax) + _2q3 * (2.0f * q1q2 + _2q3q4 - ay) + (-_4bx * q4 + _2bz * q2) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q1 + _2bz * q3) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q2 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
  norm = sqrt(s1 * s1 + s2 * s2 + s3 * s3 + s4 * s4);    // normalise step magnitude
  norm = 1.0f / norm;
  s1 *= norm;
  s2 *= norm;
  s3 *= norm;
  s4 *= norm;

  // Compute rate of change of quaternion
  qDot1 = 0.5f * (-q2 * gx - q3 * gy - q4 * gz) - beta * s1;
  qDot2 = 0.5f * (q1 * gx + q3 * gz - q4 * gy) - beta * s2;
  qDot3 = 0.5f * (q1 * gy - q2 * gz + q4 * gx) - beta * s3;
  qDot4 = 0.5f * (q1 * gz + q2 * gy - q3 * gx) - beta * s4;

  // Integrate to yield quaternion
  q1 += qDot1 * deltat;
  q2 += qDot2 * deltat;
  q3 += qDot3 * deltat;
  q4 += qDot4 * deltat;
  norm = sqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);    // normalise quaternion
  norm = 1.0f / norm;
  q[0] = q1 * norm;
  q[1] = q2 * norm;
  q[2] = q3 * norm;
  q[3] = q4 * norm;

}
double printHeading(float hx, float hy, double refrenceheading_)
{
  double new_heading ;
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

  if (heading > 0  && heading < 90)

  { if (hy < 0)
    {
      new_heading = heading;
    }
    else
    {
      new_heading = map (heading, 0, 90, 90, 180);
    }
  }
  else if (heading > 90)
  {
    new_heading = map (heading, 90, 180, -180, -90);
  }
  else
  {
    new_heading = heading;
  }

  new_heading -= refrenceheading_;
  if (new_heading > 180) new_heading -= 360;
  if (new_heading < -180) new_heading += 360;
//  Serial.print(heading );
//  Serial.print("     hx ");
//  Serial.print(hx);
//  Serial.print(" hy");
//  Serial.print(hy);
//  Serial.print("   required values ");
//  Serial.print(new_heading);
//  Serial.println("   ");
  return new_heading;

}
