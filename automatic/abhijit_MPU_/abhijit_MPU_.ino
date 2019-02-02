#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"


//MPU6050 accelgyro;
MPU6050 accelgyro(0x69); // <-- use for AD0 high

// MPU raw values  

int16_t ax, ay, az;
int16_t gx, gy, gz;

float  agnel(void);

//calman variables 


//float Gyr_rawX, Gyr_rawY, Gyr_rawZ;     //Here we store the raw data read 
    //Here we store the angle value obtained with Gyro data
 //Here we store the initial gyro data error

float rad_to_deg = 180/3.141592654;      //This value is for pasing from radians to degrees values
//float Acc_rawX, Acc_rawY, Acc_rawZ;    //Here we store the raw data read 
          //Here we store the angle value obtained with Acc data
 //Here we store the initial Acc data error



// interested values 



#define OUTPUT_READABLE_ACCELGYRO

//MPU ka jhol //
int gyro_error[4][2]={{0,0},{0,0},{0,0},{0,0}};                         //We use this variable to only calculate once the gyro data error
int acc_error[4][2]={{0,0},{0,0},{0,0},{0,0}};                          //We use this variable to only calculate once the Acc data error
float Gyro_angle_x[4][2];     
float Gyro_raw_error_x[4][2];
float Acc_angle_x[4][2];
float Acc_angle_error_x[4][2];
float Total_angle_x[4][2];
float elapsedTime[4][2], time[4][2], timePrev[4][2];   

//Declaring all the variables

float pi = 3.14159;
float a1 = 0;
float a2 = 39;
float a3 = 0;
float a4 = 39;
int relay[4][4] = {{23, 25, 27, 29}, {31, 33, 35, 37}, {39, 41, 43, 45}, {47, 49, 51, 53}};
float T[][4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
bool flag[][4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
//*****************************************************************************************************************************//
//Class for leg

class Leg
{
    int leg;  //private variable for leg number
    float X;
    float Y;
  public:
    Leg(int _leg)
    {
      leg = _leg; //declare public variable
    }
    //*************************//
    //gotopos takes X and Y and Goes to that position
    
    void gotopos(float _X, float _Y)
    {
      Serial.println("In gotopos");
      X = _X;
      Y = _Y;
      flag[0][leg] = 1;
      flag[1][leg] = 1;
    }
    //*************************//
    //choose function
    
    void choose_fn()
    {
      Serial.println("In choose_fn");
      if (X < 0)
      {
        if (flag[0][leg] == 1 || flag[1][leg] == 1)
        {
          calculate_neg_angle(X, Y);
        }
      }
      else
      {
        if (flag[0][leg] == 1 || flag[1][leg] == 1)
        {
          calculate_pos_angle(X, Y);
        }
      }
    }

    //*************************//
    //calculates angle for positive X

    void calculate_pos_angle(float X, float Y)
    {
      Serial.println("In calcpos");
      float r1 = 0;
      float phi1 = 0;
      float phi2 = 0;
      float phi3 = 0;
      r1 = sqrt(X * X + Y * Y);
      phi1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
      phi2 = atan(Y / X);
      T[0][leg] = phi2 - phi1;
      phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
      T[1][leg] = pi - phi3;
      T[0][leg] = T[0][leg] * 180 / pi;
      T[1][leg] = T[1][leg] * 180 / pi;
      onoffcontrol();
    }
    //*************************//
    //calculates angle for niggative X

    void calculate_neg_angle(float X, float Y)
    {
      Serial.println("In calcneg");
      float r1 = 0;
      float phi1 = 0;
      float phi2 = 0;
      float phi3 = 0;
      X = abs(X);
      r1 = sqrt(X * X + Y * Y);
      phi1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
      phi2 = atan(-Y / X);
      phi2 = pi + phi2;
      T[0][leg] = phi2 - phi1;
      phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
      T[1][leg] = pi - phi3;
      T[0][leg] = T[0][leg] * 180 / pi;
      T[1][leg] = T[1][leg] * 180 / pi;
      onoffcontrol();
    }
    //*************************//
    //control logic for motion

    void onoffcontrol()
    {
      //Read the feedback pot
      float fb1 = 0;
      float fb2 = 0;
      float error1 = 0;
      float error2 = 0;
      digitalWrite(8, HIGH);
      fb1 = agnel(leg,0);
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      fb2 = agnel(leg,1);
      digitalWrite(9, LOW);


      //Print statements for debugging
      Serial.print(leg);
      Serial.print("  ");
      Serial.print("  fb1  ");
      Serial.print(fb1);
      Serial.print("  T[0][leg]  ");
      Serial.print(T[0][leg]);
      Serial.print("  fb2  ");
      Serial.print(fb2);
      Serial.print("  T[1][leg]  ");
      Serial.println(T[1][leg]);

      //Find error
      error1 = T[0][leg] - fb1;
      error2 = T[1][leg] - fb2;

      //Control statements for feedback based motion
      if (abs(error1) < 2)
      {
        hardstop(relay[leg][0], relay[leg][1]);
        flag[0][leg] = 0;
      }
      if (abs(error2) < 2)
      {
        hardstop(relay[leg][2], relay[leg][3]);
        flag[1][leg] = 0;
      }

      if (fb1 < T[0][leg] && fb2 < T[1][leg])
      {
        if (flag[0][leg] == 1)
          forward(relay[leg][0], relay[leg][1]);
        if (flag[1][leg] == 1)
          forward(relay[leg][2], relay[leg][3]);
      }
      else if (fb1 < T[0][leg] && fb2 > T[1][leg])
      {
        if (flag[0][leg] == 1)
          forward(relay[leg][0], relay[leg][1]);
        if (flag[1][leg] == 1)
          backward(relay[leg][2], relay[leg][3]);
      }
      else if (fb1 > T[0][leg] && fb2 < T[1][leg])
      {
        if (flag[0][leg] == 1)
          backward(relay[leg][0], relay[leg][1]);
        if (flag[1][leg] == 1)
          forward(relay[leg][2], relay[leg][3]);
      }
      else if (fb1 > T[0][leg]  && fb2 > T[1][leg])
      {
        if (flag[0][leg] == 1)
          backward(relay[leg][0], relay[leg][1]);
        if (flag[1][leg] == 1)
          backward(relay[leg][2], relay[leg][3]);
      }
    }

    //calculating the MPU values 
    float agnel(int i, int j) 
    {
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        timePrev[i][j]=time[i][j];
        time[i][j] = millis();
        elapsedTime[i][j] = (time[i][j] - timePrev[i][j])/1000;

        gx = (gx/32.8)- Gyro_raw_error_x[i][j];
        Gyro_angle_x[i][j]=gx*elapsedTime[i][j]; 
        Acc_angle_x[i][j] = (atan((ay)/sqrt(pow((ax),2) + pow((az),2)))*rad_to_deg) - Acc_angle_error_x[i][j];
        Total_angle_x[i][j] = 0.98 *(Total_angle_x[i][j] + Gyro_angle_x[i][j]) + 0.02*Acc_angle_x[i][j];    
        Serial.print("Xº: ");
        Serial.print(Total_angle_x[i][j]); 
        Serial.println(" ");  
        return Total_angle_x[i][j];
    }
    //*************************//
    //back forward and stop functions

    void backward(int l1, int l2)
    {
      digitalWrite(l1, HIGH);
      digitalWrite(l2, LOW);
    }

    void forward(int l1, int l2)
    {
      digitalWrite(l1, LOW);
      digitalWrite(l2, HIGH);
    }

    void hardstop(int l1, int l2)
    {
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
    }
    //*************************//
};
//*****************************************************************************************************************************//

Leg leg1 = Leg(0);
Leg leg2 = Leg(1);
Leg leg3 = Leg(2);
Leg leg4 = Leg(3);


//Setup function to setup baud rate pinModes

void setup()
{
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  Serial.begin(115200);

  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  
  for (int i=0;i<4;i++)
  {
    for (int j=0;j<2;j++)
      {
        calibrate_mpu(i,j);     
      }

  }
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  //  Serial.flush();
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  delay(1000);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  delay(1000);

  Serial.println("start");

  noInterrupts();
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
  interrupts();
  leg1.gotopos(-20, 60);
  //  leg2.gotopos(-20, 60);
  //  leg3.gotopos(-20, 60);
  //  leg4.gotopos(-20, 60);

}
//*************************//
//ISR

SIGNAL(TIMER0_COMPA_vect)
{
  if (digitalRead(2) == HIGH)
  {
    Serial.println("In ISR");
    leg1.choose_fn();
    leg2.choose_fn();
    leg3.choose_fn();
    leg4.choose_fn();
  }
}
//*************************//
//loop function


void calibrate_mpu (int i , int j)
{
  
   accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
   
    if(acc_error[i][j]==0)
  {
    for(int a=0; a<200; a++)
    { 

      Acc_angle_error_x[i][j] = Acc_angle_error_x[i][j] + ((atan((ay)/sqrt(pow((ax),2) + pow((az),2)))*rad_to_deg));  
      if(a==199)
      {
        Acc_angle_error_x[i][j] = Acc_angle_error_x[i][j]/200;
        acc_error[i][j]=1;
      }
    }
  }

   if(gyro_error[i][j]==0)
  {
    for(int a=0; a<200; a++)
    {
   
      Gyro_raw_error_x[i][j] = Gyro_raw_error_x[i][j] + (gx/32.8); 
      if(a==199)
      {
      Gyro_raw_error_x[i][j]=Gyro_raw_error_x[i][j]/200;
      gyro_error[i][j]=1;
      }
    }
  }
}



void loop()
{

}
//*************************//
