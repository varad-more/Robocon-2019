#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "MegunoLink.h"
#include "SimpleKalmanFilter.h"

MPU6050 accelgyro(0x69); // <-- use for AD0 high

int e_mea = 1;
float angle;
int e_est = 1;
int q = 1 ;
int l = 0, m = 1, n = 2, o = 3;
const int no_pointer=4; 

//variables created for MPU6050 values
SimpleKalmanFilter kfx11 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy11 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfz11 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx12 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy12 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfz12 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx21 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy21 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfz21 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx22 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy22 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfz22 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx31 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy31 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfz31 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx32 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy32 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfz32 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx41 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy41 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfz41 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx42 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy42 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfz42 = SimpleKalmanFilter(e_mea, e_est, q);

//Declare constants for mpu
int16_t ax, ay, az;
int16_t gx, gy, gz;

//Declaring the variables reqd for inverse kinematics and DH parameters fro more info contact STEVE MORAIS
float pi = 3.14159;
float a1 = 0;
float a2 = 39;
float a3 = 0;
float a4 = 39;
float fb1 , fb2;
//


int pwm[4][2] = {{3, 2}, {5, 4}, {7, 6}, {9, 8}};
int driver[4][2] = {{38, 36}, {42, 40}, {47, 44}, {51, 49}};//50 KA 51,48 KA 49
int mpu [4][2] = {{22, 23}, {24, 25}, {26, 27}, {28, 29}};
int brake[4][2] = {{39, 37}, {43, 41}, {46, 45}, {50, 48}};//51 KA 50,49 KA 48
float T[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
volatile int flag[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
//volatile int flag[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
volatile int neg_flag[4] = {0, 0, 0, 0};
volatile int pos_flag[4] = {0, 0, 0, 0};
int pointer [4] = {0, 0, 0, 0};
volatile float points_leg1[4][2] = { {20, 60}, { -20, 60}, {20, 60}, { -20, 60}};
volatile float points_leg3[4][2] = { {20, 60}, { -20, 60}, {20, 60}, { -20, 60}}; //rear
volatile float points_leg2[4][2] = { { -20, 60}, {20, 60}, { -20, 60}, {20, 60}}; //front
volatile float points_leg4[4][2] = { { -20, 60}, {20, 60}, { -20, 60}, {20, 60}}; //front

class Leg
{
  public:
    volatile int leg;  //private variable for leg number
    volatile float X;
    volatile float Y;

    volatile float points[no_pointer][2];

    SimpleKalmanFilter kfx = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfy = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfz = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfx1 = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfy1 = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfz1 = SimpleKalmanFilter(e_mea, e_est, q);


    int readIndex[2] = {0, 0};
    int total[2] = {0, 0};

    int numReadings = 10;
    int readings[2][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    float  avg1, avg2;
    float fb2 = 0, fb1 = 0;
    float error1 = 0;
    float error2 = 0;
    
    Leg(int _leg, SimpleKalmanFilter _kfx, SimpleKalmanFilter _kfy, SimpleKalmanFilter _kfz, SimpleKalmanFilter _kfx1, SimpleKalmanFilter _kfy1, SimpleKalmanFilter _kfz1, volatile float _points[no_pointer][2])
    {
      leg = _leg; //declare public variable
      SimpleKalmanFilter kfx = _kfx;
      SimpleKalmanFilter kfy = _kfy;
      SimpleKalmanFilter kfz = _kfz;
      SimpleKalmanFilter kfx1 = _kfx1;
      SimpleKalmanFilter kfy1 = _kfy1;
      SimpleKalmanFilter kfz1 = _kfz1;
      for (int i = 0; i < no_pointer; i++)
      {
        for (int j = 0; j < 2; j++)
        {
          points[i][j] = _points[i][j];
        }
      }
    }
    //*************************//
    //gotopos takes X and Y and Goes to that position

    void gotopos(volatile float _X, volatile  float _Y)
    {
      X = _X;
      Y = _Y;
      flag[leg][0] = 1;
      flag[leg][1] = 1;
    }
    void chosen_fun()
    {
      if  (neg_flag[leg] == 1)
      {
        calculate_neg_angle(X, Y);
        neg_flag[leg] = 0;
      }

      if  (pos_flag[leg] == 1)
      {
        calculate_pos_angle(X, Y);
        pos_flag[leg] = 0;
      }
    }


    //*************************//
    //choose function

    void choose_fn()
    {
      //Serial.print("///a/a/a/a/");
      //Serial.println(X);
      if (X < 0)
      {
        Serial.print(" flag 1 "); Serial.print(flag[leg][0]  );   Serial.print("    flag 2   "); Serial.print(flag[leg][1]);// Serial.print("    leg   "); Serial.print(leg);

        if (flag[leg][0] == 1 || flag[leg][1] == 1)
        {
          neg_flag[leg] = 1;
        }
        /*else
          {
          neg_flag[leg] = 0;
          }*/
      }
      else if (X > 0)
      {
        if (flag[leg][0] == 1 || flag[leg][1] == 1)
        {
          pos_flag[leg] = 1;
        }
      }
      else
      {
        Serial.println("  gotopos not set");
      }
    }

    //*************************//
    //calculates angle for positive X

    void calculate_pos_angle(float X, float Y)
    {
      Serial.println("In positive");
      float r1 = 0;
      float phi1 = 0;
      float phi2 = 0;
      float phi3 = 0;
      r1 = sqrt(X * X + Y * Y);
      phi1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
      phi2 = atan(Y / X);
      T[leg][0] = phi2 - phi1;
      phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
      T[leg][1] = pi - phi3;
      T[leg][0] = T[leg][0] * 180 / pi;
      T[leg][1] = T[leg][1] * 180 / pi;
      onoffcontrol();
    }
    //*************************//
    //calculates angle for niggative X

    void calculate_neg_angle(float X, float Y)
    {
      Serial.println("In negtive");
      float r1 = 0;
      float phi1 = 0;
      float phi2 = 0;
      float phi3 = 0;
      X = abs(X);
      r1 = sqrt(X * X + Y * Y);
      phi1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
      phi2 = atan(-Y / X);
      phi2 = pi + phi2;
      T[leg][0] = phi2 - phi1;
      phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
      T[leg][1] = pi - phi3;
      T[leg][0] = T[leg][0] * 180 / pi;
      T[leg][1] = T[leg][1] * 180 / pi;
      onoffcontrol();
    }
    //*************************//
    //control logic for motion

    void onoffcontrol()
    {
      float Kp1 = 1.3, Kp2 = 45;
      int standard = 150;
      //Read the feedback pot
      digitalWrite(mpu[1][1], LOW);  digitalWrite(mpu[0][1], LOW);  digitalWrite(mpu[1][0], LOW);  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
      digitalWrite(mpu[leg][0], HIGH);
      //digitalWrite(mpu[leg][1], LOW);
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      Serial.print("#####################################leg   ");
      Serial.println(leg);
      Serial.print("X in class    "); Serial.print(X); Serial.print("        Y in class    ");
      Serial.print(Y);
      ax = kfx.updateEstimate(ax);
      az = kfy.updateEstimate(az);
      Serial.print("Link 1   angle=");
      angle = 180 * atan2(ax, az) / PI;
      fb1 = 180 - abs(angle) + 5.5 ;
      Serial.print(fb1);
      avg1 = average(fb1, 0);
      Serial.print("   ");
      Serial.print(T[leg][0]);
      digitalWrite(mpu[1][1], LOW);  digitalWrite(mpu[0][1], LOW);  digitalWrite(mpu[1][0], LOW);  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);

      digitalWrite(mpu[leg][1], HIGH);
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      ax = kfx1.updateEstimate(ax);
      az = kfy1.updateEstimate(az);
      Serial.print("Link2   angle=");
      Serial.print(" ");
      angle = 180 * atan2(ax, az) / PI;
      fb2 =  abs(angle);
      fb2 = 180 - fb2;
      fb2 = fb2 - fb1;
      Serial.print(fb2);
      Serial.print(" ");
      Serial.println(T[leg][1]);
      Serial.print(" ");
      avg2 = average(fb2, 1);
      Serial.println(avg1);
      Serial.println(avg2);
      fb1 = avg1;
      fb2 = avg2;
      digitalWrite(mpu[leg][1], LOW);
      digitalWrite(mpu[1][1], LOW);  digitalWrite(mpu[0][1], LOW);  digitalWrite(mpu[1][0], LOW);  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
      //      //Find error
      error1 = T[leg][0] - fb1;
      error2 = T[leg][1] - fb2;
      int pwm1 = (abs(error1) - abs(error2)) * Kp1 + standard;
      int pwm2 = 255;
      pwm1 = constrain(pwm1, 0, 255);
      analogWrite(pwm[leg][0], 255); //pwm1);
      analogWrite(pwm[leg][1], 255); //);

      //Control statements for feedback based motion
      if ((error1) <= 5 && (error1) >=  -5 )
      {
        analogWrite(pwm[leg][0], 0);
        hardstop(brake[leg][0]);
        flag[leg][0] = 0;
        Serial.print(pwm[leg][0]);
        Serial.println("L1 stop");
      }
      else
      {
        flag[leg][0] = 1;
        Serial.println("L1 start");
      }
      if ((error2) <= 5 && (error2) >= -5 )
      {
        analogWrite(pwm[leg][1], 0);
        hardstop(brake[leg][1]);
        flag[leg][1] = 0;
        Serial.print(pwm[leg][1]);
        Serial.println("L2 stop");
      }
      else
      {
        flag[leg][1] = 1;
        Serial.println("L2 start");
      }

      if (fb1 < T[leg][0] && fb2 < T[leg][1])
      {
        if (flag[leg][0] == 1)
        {
          //          forward(relay[leg][0], relay[leg][1]);
          backward(driver[leg][0], brake[leg][0]);
          Serial.print("link one increase angle"); Serial.print(" "); Serial.print (driver[leg][0]); Serial.print(" "); Serial.print (driver[leg][1]);
        }
        if (flag[leg][1] == 1)
        {
          forward(driver[leg][1], brake[leg][1]);
          Serial.print("link two  increase angle"); Serial.print(" "); Serial.print (driver[leg][2]); Serial.print(" "); Serial.print (driver[leg][3]);
        }
      }
      else if (fb1 < T[leg][0] && fb2 > T[leg][1])
      {
        if (flag[leg][0] == 1)
        {
          //          forward(driver[leg][0], driver[leg][1]);
          backward(driver[leg][0], brake[leg][0]);
          Serial.print("link one  increase angle"); Serial.print(" "); Serial.print (driver[leg][0]); Serial.print(" "); Serial.print (driver[leg][1]);
        }
        if (flag[leg][1] == 1)
        {
          backward(driver[leg][1],  brake[leg][1]);
          Serial.print("link two decrease angle"); Serial.print(" "); Serial.print (driver[leg][2]); Serial.print(" "); Serial.print (driver[leg][3]);
        }
      }
      else if (fb1 > T[leg][0] && fb2 < T[leg][1])
      {
        if (flag[leg][0] == 1)
        {
          //          backward(driver[leg][0], driver[leg][1]);
          forward(driver[leg][0], brake[leg][0]);
          Serial.print("link one decrease angle"); Serial.print(" "); Serial.print (driver[leg][0]); Serial.print(" "); Serial.print (driver[leg][1]);
        }
        if (flag[leg][1] == 1)
        {
          forward(driver[leg][1], brake[leg][1]);

          Serial.print("link two  increase angle"); Serial.print(" "); Serial.print (driver[leg][2]); Serial.print(" "); Serial.print (driver[leg][3]);
        }
      }
      else if (fb1 > T[leg][0]  && fb2 > T[leg][1])
      {
        if (flag[leg][0] == 1)
        {
          //          backward(driver[leg][0], driver[leg][1]);
          forward(driver[leg][0], brake[leg][0]);
          Serial.print("link one decrease angle"); Serial.print(" "); Serial.print (driver[leg][0]); Serial.print(" "); Serial.print (driver[leg][1]);
        }
        if (flag[leg][1] == 1)
        {
          backward(driver[leg][1], brake[leg][1]);
          Serial.print("link two  decrease angle"); Serial.print(" "); Serial.print (driver[leg][2]); Serial.print(" "); Serial.print (driver[leg][3]);
        }
      }
      Serial.print("flag");
      Serial.print(flag[leg][0]);
      Serial.print(flag[leg][1]);
    }
    //*************************//
    //back forward and stop functions

    void backward(int l1, int l2)
    {
      // actuator opening
      digitalWrite(l2, LOW);
      digitalWrite(l1, LOW);

    }

    void forward(int l1, int l2)
    {
      // actuator closing
      digitalWrite(l2, LOW);
      digitalWrite(l1, HIGH);

    }

    void hardstop(int l1)
    {
      digitalWrite(l1, HIGH);
    }
    void check_point()
    {
      {
        pointer[leg] = pointer[leg] + 1;
        if (pointer[leg] == no_pointer  )
        {
          pointer[leg] = 0;
        }
        Serial.print(" incermented pointer ");
        gotopos(points[pointer[leg]][0], points[pointer[leg]][1]);
      }
    }

    float average(int val, int leg)
    {
      total[leg] = total[leg] - readings[leg][readIndex[leg]];
      // read from the sensor:
      readings[leg][readIndex[leg]] = val;
      // add the reading to the total:
      total[leg] = total[leg] + readings[leg][readIndex[leg]];
      // advance to the next position in the array:
      readIndex[leg] = readIndex[leg] + 1;
      // if we're at the end of the array...
      if (readIndex[leg] >= numReadings) {
        // ...wrap around to the beginning:
        readIndex[leg] = 0;
      }
      // calculate the average:
      return (total[leg] / numReadings);
    }
    //*************************//
};




//*****************************************************************************************************************************//
//
Leg leg1 = Leg(0, kfx11, kfy11, kfz11, kfx12, kfy12, kfz12, points_leg1);
Leg leg2 = Leg(1, kfx21, kfy21, kfz21, kfx22, kfy22, kfz22, points_leg2);
Leg leg3 = Leg(2, kfx31, kfy31, kfz31, kfx32, kfy32, kfz32, points_leg3);
Leg leg4 = Leg(3, kfx41, kfy41, kfz41, kfx42, kfy42, kfz42, points_leg4);


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  for (int i = 0 ; i < 4; i++)
  {
    for (int j = 0 ; j < 2; j++)
    {
      pinMode(driver[i][j], OUTPUT);
    }
  }
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      pinMode(mpu[i][j], OUTPUT);
      digitalWrite(mpu[i][j], LOW);
    }
  }
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      pinMode(brake[i][j], OUTPUT);
    }
  }
  for (int i = 0 ; i < 4; i++)
  {
    for (int j = 0 ; j < 2; j++)
    {
      pinMode(pwm[i][j], OUTPUT);
    }
  }
  // yet to initialize the herrcules motor driver

  //
  float angle_z[8];

  digitalWrite(mpu[0][0], HIGH); digitalWrite(mpu[0][1], LOW); digitalWrite(mpu[1][0], LOW); digitalWrite(mpu[1][1], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
  Serial.print("l1l1        ");
  Serial.print(mpu[0][0]);
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {
    float  avg1, angle, angl_z;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg1.kfx.updateEstimate(ax);
    az = leg1.kfy.updateEstimate(az);
    ay = leg1.kfz.updateEstimate(ay);
    angle = 180 * atan2(ax, az) / PI;
    angle_z[0] = 180 * atan2(ay, az) / PI;

    fb1 = abs(angle) - 5.5 ; // fb1=180- abs(angle) -5 ;
    fb1 = 180 - fb1;
    //    Serial.print(fb1/);
    avg1 = leg1.average(fb1, 0);
  }



  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[0][1], HIGH); digitalWrite(mpu[1][0], LOW); digitalWrite(mpu[1][1], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
  Serial.println("l1l2     ");
  Serial.print(mpu[0][1]);
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {
    float fb2, avg2, angle;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg1.kfx1.updateEstimate(ax);
    az = leg1.kfy1.updateEstimate(az);
    ay = leg1.kfz1.updateEstimate(ay);
    angle = 180 * atan2(ax, az) / PI;
    angle_z[1] = 180 * atan2(ay, az) / PI;

    fb2 =  abs(angle);
    fb2 = fb2 - fb1;

    avg2 = leg1.average(fb2, 1);
  }

  //
  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[0][1], LOW); digitalWrite(mpu[1][0], HIGH); digitalWrite(mpu[1][1], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
  Serial.print("l2l1    ");
  Serial.print(mpu[1][0]);
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {
    float  avg1, angle;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg2.kfx.updateEstimate(ax);
    az = leg2.kfy.updateEstimate(az);
    ay = leg2.kfz.updateEstimate(ay);

    angle = 180 * atan2(ax, az) / PI;
    angle_z[2] = 180 * atan2(ay, az) / PI;

    fb1 = abs(angle) - 5.5 ; // fb1=180- abs(angle) -5 ;
    fb1 = 180 - fb1;
    avg1 = leg2.average(fb1, 0);
    //   / Serial.print(fb1);
    //    /avg1 = leg2.average(fb1, 0);
  }

  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[0][1], LOW); digitalWrite(mpu[1][0], LOW); digitalWrite(mpu[1][1], HIGH); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
  Serial.print("l2l2    ");
  Serial.print(mpu[1][1]);
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {
    float fb2, avg2, angle;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg2.kfx1.updateEstimate(ax);
    az = leg2.kfy1.updateEstimate(az);
    ay = leg2.kfz1.updateEstimate(ay);
    angle_z[3] = 180 * atan2(ay, az) / PI;
    angle = 180 * atan2(ax, az) / PI;

    fb2 =  abs(angle);
    fb2 = 180 - fb2;
    fb2 = fb2 - fb1;
    avg2 = leg2.average(fb2, 1);
    ///avg2 = leg2.average(fb2, 1);
  }

  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[0][1], LOW); digitalWrite(mpu[1][0], LOW); digitalWrite(mpu[1][1], LOW); digitalWrite(mpu[2][0], HIGH); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
  Serial.print("l3l1    ");
  Serial.print(mpu[2][0]);
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {
    float  avg1, angle;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg3.kfx.updateEstimate(ax);
    az = leg3.kfy.updateEstimate(az);
    ay = leg3.kfz.updateEstimate(ay);
    angle_z[4] = 180 * atan2(ay, az) / PI;
    angle = 180 * atan2(ax, az) / PI;

    fb1 = abs(angle) - 5.5 ; // fb1=180- abs(angle) -5 ;
    fb1 = 180 - fb1;
    avg1 = leg3.average(fb1, 0);
    ///avg2 = leg2.average(fb2, 1);
  }

  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[0][1], LOW); digitalWrite(mpu[1][0], LOW); digitalWrite(mpu[1][1], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], HIGH); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
  Serial.print("l3l2    ");
  Serial.print(mpu[2][1]);
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {
    float fb2, avg2, angle;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg3.kfx1.updateEstimate(ax);
    az = leg3.kfy1.updateEstimate(az);
    ay = leg3.kfz1.updateEstimate(ay);
    angle_z[5] = 180 * atan2(ay, az) / PI;
    angle = 180 * atan2(ax, az) / PI;

    fb2 =  abs(angle);
    fb2 = 180 - fb2;
    fb2 = fb2 - fb1;
    avg2 = leg3.average(fb2, 1);
    ///avg2 = leg2.average(fb2, 1);
  }

  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[0][1], LOW); digitalWrite(mpu[1][0], LOW); digitalWrite(mpu[1][1], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], HIGH); digitalWrite(mpu[3][1], LOW);
  Serial.print("l4l1    ");
  Serial.print(mpu[3][0]);
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {
    float  avg1, angle;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg4.kfx.updateEstimate(ax);
    az = leg4.kfy.updateEstimate(az);
    ay = leg4.kfz.updateEstimate(ay);
    angle_z[6] = 180 * atan2(ay, az) / PI;
    angle = 180 * atan2(ax, az) / PI;

    fb1 = abs(angle) - 5.5 ; // fb1=180- abs(angle) -5 ;
    fb1 = 180 - fb1;
    avg1 = leg4.average(fb1, 0);

    ///avg2 = leg2.average(fb2, 1);
  }

  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[0][1], LOW); digitalWrite(mpu[1][0], LOW); digitalWrite(mpu[1][1], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], HIGH);
  Serial.print("l4l2    ");
  Serial.print(mpu[3][1]);
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  { float fb2, avg2, angle;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg4.kfx1.updateEstimate(ax);
    az = leg4.kfy1.updateEstimate(az);
    ay = leg4.kfz1.updateEstimate(ay);
    angle_z[7] = 180 * atan2(ay, az) / PI;
    angle = 180 * atan2(ax, az) / PI;

    fb2 =  abs(angle);
    fb2 = 180 - fb2;
    fb2 = fb2 - fb1;
    avg2 = leg4.average(fb2, 1);

    ///avg2 = leg2.average(fb2, 1);
  }
  digitalWrite(mpu[1][1], LOW);  digitalWrite(mpu[0][1], LOW);  digitalWrite(mpu[1][0], LOW);  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
  //Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  Serial.print(" "); Serial.print(mpu[0][0]); Serial.print(" "); Serial.print(mpu[0][1]); Serial.print(" "); Serial.print(mpu[1][0]); Serial.print(" "); Serial.print(mpu[1][1]);


}

void loop() {
  // put your main code here, to run repeatedly:

}

float * average_z (float *z_array )
{
  static float average[4];
  static int readIndex[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int total[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  //double val = z_array ;
  int numReadings = 10;
  float readings[8][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  float  avgz[8];

  for (int j = 0 ; j < 8; j++)
  {
    for (int k=0;k<10;k++)
    {
    total[j] = total[j] - readings[readIndex[j]][k];
    // read from the sensor:
    readings[readIndex[j]][k] = z_array[j];
    // add the reading to the total:
    total[j] = total[j] + readings[readIndex[j]][k];
    // advance to the next position in the array:
    readIndex[k] = readIndex[k] + 1;
    // if we're at the end of the array...
    if (readIndex[j] >= numReadings) {
      // ...wrap around to the beginning:
      readIndex[k] = 0;
      avgz[j] = total[j] / numReadings;
    }
    }
  }
  for (int i = 0; i < 4; i++)
  {
    average[i] = ((avgz[i] + avgz[i + 1]) / 2);
  }
  return average;
}
