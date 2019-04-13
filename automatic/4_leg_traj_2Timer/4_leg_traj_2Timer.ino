// this code is for driver recieved from robukits having direction pin ,brake pin , and pwm pin
//Include all libraries

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "MegunoLink.h"
#include "SimpleKalmanFilter.h"

volatile int a = 0;
/**********************************************/
//MPU6050 accelgyro; // <--use for AD0 floating

MPU6050 accelgyro(0x69); // <-- use for AD0 high

int e_mea = 1;
float angle;
int e_est = 1;
int q = 1 ;
int l = 0, m = 1, n = 2, o = 3;
SimpleKalmanFilter kfx11 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy11 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx12 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy12 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx21 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy21 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx22 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy22 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx31 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy31 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx32 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy32 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx41 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy41 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx42 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy42 = SimpleKalmanFilter(e_mea, e_est, q);

//e_mea: Measurement Uncertainty - How much do we expect to our measurement vary
//e_est: Estimation Uncertainty - Can be initilized with the same value as e_mea since the kalman filter will adjust its value.
//q: Process Variance - usually a small number between 0.001 and 1 - how fast your measurement moves. Recommended 0.01. Should be tunned to your needs.
//                                                               ^
/**********************************************/
//Declare constants for mpu
int16_t ax, ay, az;
int16_t gx, gy, gz;

//Declaring all the variables

float pi = 3.14159;
float a1 = 0;
float a2 = 39;
float a3 = 0;
float a4 = 39;
float fb1 , fb2;
//



///volatile
const int  no_pointer = 4;
int pwm[4][2] = {{13, 12}, {11, 10}, {9, 8}, {7, 6}};
int driver[4][2] = {{25, 29}, {33, 37}, {41, 45}, {49, 53}}; //50 KA 51,48 KA 49
int mpu [4][2] = {{38 , 40}, {42, 44}, {46, 48}, {50, 52}}; //yet to go
int brake[4][2] = {{23, 27}, {31, 35}, {39, 43}, {47, 51}}; //51 KA 50,49 KA 48
float T[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
volatile int flag[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
volatile int neg_flag[4] = {0, 0, 0, 0};
volatile int pos_flag[4] = {0, 0, 0, 0};
int pointer [4] = {0, 0, 0, 0};
//volatile int sign_flag[4] = {2,2,2,2};

boolean b; ///uiadhfiuahdif
//volatile float points[9][2] = {{-19.34,54.90},{-17.3,49.96},{-13.4,45.153},{9.8,42.66},{13.7,45.429},{17.2,49.79},{19.3,54.755},{20,60},{-20,60} };
//
//volatile float points_leg1[4][2] = {{1, 50}, {15, 60}, {1, 60}, { -15, 60}}; //, { -20, 60} }; // rear
volatile float points_leg1[4][2] = { {20, 60}, { -20, 60}, {20, 60}, { -20, 60}};
volatile float points_leg3[4][2] = { {20, 60}, { -20, 60}, {20, 60}, { -20, 60}}; //rear
volatile float points_leg2[4][2] = { { -20, 60}, {20, 60}, { -20, 60}, {20, 60}}; //front
volatile float points_leg4[4][2] = { { -20, 60}, {20, 60}, { -20, 60}, {20, 60}}; //front


//volatile float points_leg1[1][2] = {{20, 60}};//, {15, 60}, {1, 60}, { -15, 60}}; //, { -20, 60} }; // rear
//volatile float points_leg3[4][2] = {{ -20, 60}, {1, 50}, {20, 60}, {5, 60}}; //rear
//volatile float points_leg2[4][2] = {{ -20, 60}, {1, 60}, {20, 60}, {1, 50}}; //front
//volatile float points_leg4[4][2] = {{1, 60}, {20, 60}, {1, 50}, { -20, 60}}; //front



//volatile float points[10][2] = {/*{0, 55.15}, { 0 , 54.15}, { 0, 53.15}, { 0, 52.15}, { 0, 51.15},*/ { 0, 50.15}, { -6, 51.15}, { -8, 52.15}, { -9.17, 53.15}, { -9.8, 54.15}, { -10, 55.15}, { -9.8, 56.15}, { -9.17, 57.15}, { -8, 58.15}, { -6, 59.15}};
//volatile float points[36][2] = { { 0, 55.15}, { 0, 54.15}, { 0, 53.15}, { 0, 52.15}, { 0, 51.15}, { 0, 50.15}, { -6, 51.15}, { -8, 52.15}, { -9.17, 53.15}, { -9.8, 54.15},{-10, 55.15},{ -9, 55.15},{-8,55.15},{-7,55.15},{-6,55.15},{-5,55.15},{-4,55.15},{-3,55.15},{-2,55.15},{-1,55.15},{0,55.15},{1,55.15},{2,55.15},{3,55.15},{4,55.15},{5,55.15},{6,55.15},{7,55.15},{8,55.15},{9,55.15},{10,55.15},{9.8,54.15},{9.17,53.15},{8,52.15},{6,51.15},{0.50.15} };
//volatile
//volatile int pointer1 = 0,pointer2 = 0,pointer3 = 0,pointer4 = 0;
/*****************************************************************************************************************************/
//Class for leg

//class next_leg
//{
//  Leg current_leg;
//  public:
//
//};
class Leg
{
  public:
    volatile int leg;  //private variable for leg number
    volatile float X;
    volatile float Y;

    volatile float points[no_pointer][2];

    SimpleKalmanFilter kfx = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfy = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfx1 = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfy1 = SimpleKalmanFilter(e_mea, e_est, q);

    int readIndex[2] = {0, 0};
    int total[2] = {0, 0};

    int numReadings = 10;
    int readings[2][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    float  avg1, avg2;
    float fb2 = 0, fb1 = 0;
    float error1 = 0;
    float error2 = 0;
    Leg(int _leg, SimpleKalmanFilter _kfx, SimpleKalmanFilter _kfy, SimpleKalmanFilter _kfx1, SimpleKalmanFilter _kfy1, volatile float _points[no_pointer][2])
    {
      leg = _leg; //declare public variable
      SimpleKalmanFilter kfx = _kfx;
      SimpleKalmanFilter kfy = _kfy;
      SimpleKalmanFilter kfx1 = _kfx1;
      SimpleKalmanFilter kfy1 = _kfy1;
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
      // Serial.println(" ");
      X = _X;
      Y = _Y;
      flag[leg][0] = 1;
      flag[leg][1] = 1;

      // Serial.print(X);
      //Serial.print("  ");
      // Serial.print(Y);
    }
    void chosen_fun()
    {
      // Serial.print("///a/a/a/a/");
      //Serial.println(X);

      //Serial.print(" sign flag 1 "); Serial.print(neg_flag[leg]  );   Serial.print("   sign flag 2   "); Serial.println(pos_flag[leg]);
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
        /*else
          {
          pos_flag[leg] = 0;
          }*/
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
      //
      //      r1 = sqrt(X * X + Y * Y);
      //      phi1 = (acos((r1 * r1 + a2 * a2 - a4 * a4) / (2 * a2 * r1))) * 180. / PI;
      //      phi2 = (atan(Y / X)) * 180 / PI;
      //      phi3 = (acos((a2 * a2 + a4 * a4 - r1 * r1) / (2 * a2 * a4))) * 180. / PI;
      //      T[0][leg] = phi1 + phi2;
      //      T[1][leg] = phi3 + T[0][leg] - 180;
      //      T[0][leg] = 180 - T[0][leg] ;/
      //      T[1][leg] = 180 - T[1][leg] ;/
      //steve changes
      //      T[0][leg] = 180 - T[0][leg];
      //      T[1][leg] = 180 - T[1][leg];

      //      T[0][leg] = T[0][leg] - 90;
      /*********************/
      //       r1 = sqrt(X * X + Y * Y);
      //      phi1 = acos(((r1 * r1) + (a2 * a2) - (a4 * a4)) / (2.0 * a2 * r1));
      //      phi2 = atan(Y / X);
      //      phi3 = (acos(((a4 * a4) + (a2 * a2) - (r1 * r1)) / (2.0 * a2 * a4)))*180/PI;
      //      T[0][leg] = (phi2 + phi1)*180/PI;
      //      T[1][leg] = -(phi3 + T[0][leg] - 180);
      onoffcontrol();
    }
    //*************************//
    //calculates angle for niggative X

    void calculate_neg_angle(float X, float Y)
    {
      Serial.println("In negtive");
      //Serial.println("In calcneg");
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
      //      T[1/][leg] = phi3 + T[0][leg] - 180;
      //      //steve

      //      r1 = sqrt(X * X + Y * Y);
      //      phi1 = (acos((r1 * r1 + a2 * a2 - a4 * a4) / (2 * a2 * r1))) * 180. / PI;
      //      phi2 = (atan(-Y / X)) * 180 / PI; // Here X is negetive so, in k2 it is multipled by negetive sign.
      //      phi3 = (acos((a2 * a2 + a4 * a4 - r1 * r1) / (2 * a2 * a4))) * 180. / PI;
      //      T[0][leg] = phi1 + phi2;
      //      T[1][leg] = phi3 + T[0][leg] - 180;
      //      T[0][leg] = 180 - T[0][leg] ;/
      //      T[1][leg] = 180 - T[1][leg] ;/

      //   T[0][leg] = 180 - T[0][leg];
      //      T[1][leg] = 180 - T[1][leg]'
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
      Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
      Serial.print("#####################################leg   ");
      Serial.println(leg);
      Serial.print("X in class    "); Serial.print(X); Serial.print("        Y in class    ");
      Serial.print(Y);
      ax = kfx.updateEstimate(ax);
      az = kfy.updateEstimate(az);
      Serial.print("Link 1   angle=");
      angle = 180 * atan2(ax, az) / PI;
      fb1 = 180 - abs(angle) - 5.5 ;
      Serial.print(fb1);
      avg1 = average(fb1, 0);
      Serial.print("   ");
      Serial.print(T[leg][0]);
      digitalWrite(mpu[1][1], LOW);  digitalWrite(mpu[0][1], LOW);  digitalWrite(mpu[1][0], LOW);  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);

      digitalWrite(mpu[leg][1], HIGH);
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
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
      //      int pwm1 = int((error1) * Kp1 * (abs(error1) - abs(error2)) + standard);
      //      int pwm2 = int((error2) * Kp2 * (pow(1.7, (-abs(error1) + 20)) + 1) + standard);
      pwm1 = constrain(pwm1, 0, 255);
      //      pwm2 = constrain(pwm2, 0, 255);


      analogWrite(pwm[leg][0], 255); //pwm1);
      analogWrite(pwm[leg][1], 255); //);

      //      Serial.print(" ");
      //      Serial.print(p/wm[leg][0]);
      //      Serial.print(pwm[/leg][1]);
      //Control statements for feedback based motion
      if ((error1) <= 5 && (error1) >=  -5 )
      {
        //hardstop(relay[leg][0], relay[leg][1]);
        analogWrite(pwm[leg][0], 0);
        hardstop(brake[leg][0]);
        flag[leg][0] = 0;
        Serial.print(pwm[leg][0]);
        Serial.println("L1 stop");
        //Serial.println(flag[0][0]);
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
        //Serial.println(flag[0][1]);
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
      Serial.println(flag[leg][1]);
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
      //      Serial.println("IN CHECKPOINT");
      // if (flag[0][0] == 0 && flag[0][1] == 0 )//&& flag[1][0] == 0 && flag[1][1] == 0 && flag[2][0] == 0 && flag[2][1] == 0 && flag[3][0] == 0 && flag[3][1] == 0 )
      {
        //        Serial.println("NEXT POINT");
        pointer[leg] = pointer[leg] + 1;
        if (pointer[leg] == no_pointer  )
        {
          pointer[leg] = 0;
          //pointer[1] = 0;
          //pointer[2] = 0;
          //pointer[3] = 0;

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
Leg leg1 = Leg(0, kfx11, kfy11, kfx12, kfy12, points_leg1);
Leg leg2 = Leg(1, kfx21, kfy21, kfx22, kfy22, points_leg2);
Leg leg3 = Leg(2, kfx31, kfy31, kfx32, kfy32, points_leg3);
Leg leg4 = Leg(3, kfx41, kfy41, kfx42, kfy42, points_leg4);
//Leg leg[4] = {Leg(0, kfx11, kfy11, kfx12, kfy12, points_leg1), Leg(1, kfx21, kfy21, kfx22, kfy22, points_leg2), Leg(2, kfx31, kfy31, kfx32, kfy32, points_leg3), Leg(3, kfx41, kfy41, kfx42, kfy42, points_leg4)};
//Leg leg3 = Leg(2);
//Leg leg4 = Leg(3);


//Setup function to setup baud rate pinModes

void setup()
{
  Wire.begin();
  Wire.setClock(10000);
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


  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[0][1], LOW); digitalWrite(mpu[1][0], LOW); digitalWrite(mpu[1][1], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
  //delay(10000);
  Serial.println("waiting for 1 sec");
  digitalWrite(mpu[0][0], HIGH); digitalWrite(mpu[0][1], LOW); digitalWrite(mpu[1][0], LOW); digitalWrite(mpu[1][1], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
  Serial.print("l1l1     ");
  Serial.print(mpu[0][0]);
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {
    float  avg1, angle;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg1.kfx.updateEstimate(ax);
    az = leg1.kfy.updateEstimate(az);

    //    Serial.print("Leg1   an/gle=");
    //      Serial.print(ax);
    //      Serial.print(" ");
    angle = 180 * atan2(ax, az) / PI;

    fb1 = 180 - abs(angle) - 5.5 ; // fb1=180- abs(angle) -5 ;
    avg1 = leg1.average(fb1, 0);
  }


  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[0][1], HIGH); digitalWrite(mpu[1][0], LOW); digitalWrite(mpu[1][1], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
  Serial.print("l1l2     ");
  Serial.print(mpu[0][1]);
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {
    float fb2, avg2, angle;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg1.kfx1.updateEstimate(ax);
    az = leg1.kfy1.updateEstimate(az);
    //    Serial.print("Leg2   angle/=");
    //      Serial.print(ax);
    //    Serial.print(" "/);
    angle = 180 * atan2(ax, az) / PI;
    fb2 =  abs(angle);
    fb2 = 180 - fb2;
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
    angle = 180 * atan2(ax, az) / PI;

    fb1 = 180 - abs(angle) - 5.5 ; // fb1=180- abs(angle) -5 ;
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
    angle = 180 * atan2(ax, az) / PI;
    fb1 = 180 - abs(angle) - 5.5 ; // fb1=180- abs(angle) -5 ;
    avg1 = leg3.average(fb1, 0);
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
    angle = 180 * atan2(ax, az) / PI;
    fb2 =  abs(angle);
    fb2 = 180 - fb2;
    fb2 = fb2 - fb1;
    avg2 = leg3.average(fb2, 1);
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
    angle = 180 * atan2(ax, az) / PI;
    fb1 = 180 - abs(angle) - 5.5 ; // fb1=180- abs(angle) -5 ;
    avg1 = leg4.average(fb1, 0);
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
    angle = 180 * atan2(ax, az) / PI;
    fb2 =  abs(angle);
    fb2 = 180 - fb2;
    fb2 = fb2 - fb1;
    avg2 = leg4.average(fb2, 1);
  }
  digitalWrite(mpu[1][1], LOW);  digitalWrite(mpu[0][1], LOW);  digitalWrite(mpu[1][0], LOW);  digitalWrite(mpu[0][0], LOW); digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);



  //Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  Serial.print(" "); Serial.print(mpu[0][0]); Serial.print(" "); Serial.print(mpu[0][1]); Serial.print(" "); Serial.print(mpu[1][0]); Serial.print(" "); Serial.print(mpu[1][1]);
  delay(5000);
  Serial.println("start");



  // initialize timer1

  noInterrupts();           // disable all interrupts

  TCCR1A = 0 ;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 5000;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescalerp
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
    Serial.print("8==========D");

//  // timer 2 
//  TCCR2A = 0;// set entire TCCR2A register to 0
//  TCCR2B = 0;// same for TCCR2B
//  TCNT2  = 0;//initialize counter value to 0
//  // set compare match register for 8khz increments
//  OCR2A = 31250;// = (16*10^6) / (8000*8) - 1 (must be <256)
//  // turn on CTC mode
//  TCCR2A |= (1 << WGM21);
//  // Set CS21 bit for 8 prescaler
//  TCCR2B |= (1 << CS21);   
//  // enable timer compare interrupt
//  TIMSK2 |= (1 << OCIE2A);


  
  interrupts();             // enable all interrupts
  Serial.println("Set points");

  leg1.gotopos(20, 60);
  leg2.gotopos(20, 60);
  leg3.gotopos(20, 60);
  leg4.gotopos(20, 60);
  //leg2.gotopos(20, 60);

  Serial.println("done with this ");
  //  leg2.gotopos(-20, 60);
  //  leg3.gotopos(-20, 60);
  //  leg4.gotopos(-20, 60);

}
//*************************//
//ISR

SIGNAL(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  Serial.println("ISR");
  //cli();
  OCR1A = 5000;
// // sei();

 // leg1.choose_fn();
 // leg2.choose_fn();
 // leg3.choose_fn();
  leg4.choose_fn();

  //  if  (/*flag[0][0] == 0 && flag[0][1] == 0 )*//*&&*/ flag[1][0] == 0 && flag[1][1] == 0  /*//&&flag[2][0] == 0 && flag[2][1] == 0 )//*/&&*/ flag[3][0] == 0 && flag[3][1] == 0 )/
 // Serial.println("*#*#*#*#*#*#*#*");
 // Serial.print(flag[1][0]);
 // Serial.print("    ");
//  Serial.println(flag[1][1]);
  if  ( flag[3][0] == 0 && flag[3][1] == 0 )//&& flag[1][0] == 0 && flag[1][1] == 0 && flag[2][0] == 0 && flag[2][1] == 0 && flag[3][0] == 0 && flag[3][1] == 0 )
  {
    Serial.println("Passed Condition");
   // leg1.check_point();
   // leg2.check_point();
   // leg3.check_point();
    leg4.check_point();

    //    leg1.gotopos(leg1.points[pointer][0], leg1.points[pointer][1]);
    //   leg2.gotopos(leg2.points[pointer][0], leg2.points[pointer][1]);
    //  leg3.gotopos(leg3.points[pointer][0], leg3.points[pointer][1]);
    //leg4.gotopos(leg4.points[pointer][0], leg4.points[pointer][1]);
  }
  //sei();

}

//SIGNAL(TIMER2_COMPA_vect)
//{
// // cli();
//  OCR2A = 31250;
//  digitalWrite(mpu[3][0], HIGH); digitalWrite(mpu[3][1], LOW); //digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
// // Serial.print("l4l1    ");
// // Serial.print(mpu[3][0]);
//  accelgyro.initialize();
// // Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
//   
//  digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1],HIGH);// digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
//  //Serial.print("l4l2    ");
//  //Serial.print(mpu[3][1]);
//  accelgyro.initialize();
//  //Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
// // sei();
//}
//*************************//
//loop function


void loop()
{
  //  leg1 = leg4/t
  Serial.println("LOOPLOOPLOOPLOOPLOOPLOOP");
  // Serial.println(a);
   
   digitalWrite(mpu[3][0], HIGH); digitalWrite(mpu[3][1], LOW); //digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
// // Serial.print("l4l1    ");
// // Serial.print(mpu[3][0]);
  accelgyro.initialize();
// // Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
//   
  digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1],HIGH);// digitalWrite(mpu[2][0], LOW); digitalWrite(mpu[2][1], LOW); digitalWrite(mpu[3][0], LOW); digitalWrite(mpu[3][1], LOW);
//  //Serial.print("l4l2    ");
//  //Serial.print(mpu[3][1]);
  accelgyro.initialize();
//  //Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  //Serial.print(pointer);
  //Serial.print(points_leg1[pointer][0]);
  //Serial.println("  (      .     )    ");
  //Serial.print(points_leg1[pointer][1]);

  leg4.chosen_fun();
  //Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  //leg2.chosen_fun();
  //leg3.chosen_fun();
  //leg4.chosen_fun();
  //Serial.flush();
  //leg1.onoffcontrol();
  //leg2.onoffcontrol();
  //leg3.onoffcontrol();
  //leg4.onoffcontrol();
  //leg2.chosen_fun();
  //*************************//
}
