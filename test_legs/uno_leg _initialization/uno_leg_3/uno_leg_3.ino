
/////////////////////////////////////////////////////
// libraries
#include "I2Cdev.h" // MPU to arduino connection
#include "MPU6050.h"  // MPU6050
#include "Wire.h"  //reqiured library for i2c connection
#include "MegunoLink.h"  //used to plot data ; not yet used in the code
#include "SimpleKalmanFilter.h"  //used to filter the raw values of MPU6050 


//class of MPU
MPU6050 accelgyro(0x69); // <-- use for AD0 high ; the AD0 pin should be high of particular MPU for the utilization of that sensor

//
int pointer = 0;

//variables reqd for initialzing the kalman filter
int e_mea = 1;
int e_est = 1;
int q = 1 ;
//object of the kalman filter
SimpleKalmanFilter kfx11 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy11 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx12 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy12 = SimpleKalmanFilter(e_mea, e_est, q);
/*e_mea: Measurement Uncertainty - How much do we expect to our measurement vary
  e_est: Estimation Uncertainty - Can be initilized with the same value as e_mea since the kalman filter will adjust its value.
  q: Process Variance - usually a small number between 0.001 and 1 - how fast your measurement moves. Recommended 0.01. Should be tunned to your needs.
*/
//constants of MPU
int16_t ax, ay, az;
int16_t gx, gy, gz;

int X, Y;

// variables - inverse kinematics
float pi = 3.14159;
float a1 = 0;
float a2 = 39;
float a3 = 0;
float a4 = 39;

int dir[2] = {12, 13}; //dir-pins
int pwm[2] = {5, 6}; //pwm-pins
int brake[2] = {4, 7}; //brake-pins
int mpu[2] = {9, 10}; //mpu-pins

//volatile float points[4][2] = { {20, 60}, { -20, 60}, {20, 60}, { -20, 60}};
//Pehele wale acche points :)
//volatile float points[4][2] = { { 20, 60}, { 1, 60}, {-10, 60}, { 5, 55}}; // leg -0
//volatile float points[4][2] = { {20, 60}, { 5, 55}, {-10, 60}, { 1, 60}};  // leg -1
//volatile float points[4][2] = { {-10, 60}, { 5, 55}, {20, 60}, { 1, 60}};  // leg -2
//volatile float points[4][2] = { {-10, 60}, { 1, 60}, { 20, 60}, { 5 , 50}}; // leg -3



//volatile float points[4][2] = { { -10, 60}, {5, 55}, {20, 60}, {1, 60}}; // leg -0
//volatile float points[4][2] = { {-10, 60}, {1, 60}, {20, 60}, {5, 55}}; // leg -1
//volatile float points[4][2] = { {20, 60}, {1, 60}, { -10, 60}, {5, 55}}; // leg -2
volatile float points[4][2] = { { 5, 60}, {-5 , 50}, {-20, 60}, {1, 60}}; // leg -3


float T[2] = {0, 0};
volatile int flag[2] = {0, 0};
volatile int neg_flag = 0;
volatile int pos_flag = 0;

int readIndex[2] = {0, 0};
int total[2] = {0, 0};

int numReadings = 10;
int readings[2][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
float  avg1, avg2;
float fb2 = 0, fb1 = 0;
float error1 = 0;
float error2 = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  pinMode(1, INPUT);
  Wire.begin();
  Wire.setClock(10000);
  Serial.begin(115200);
  for (int j = 0 ; j < 2; j++)
  {
    pinMode(dir[j], OUTPUT); delay(50);
  }


  for (int j = 0; j < 2; j++)
  {
    pinMode(mpu[j], OUTPUT); delay(50);
    digitalWrite(mpu[j], LOW); delay(50);
  }

  for (int j = 0; j < 2; j++)
  {
    pinMode(brake[j], OUTPUT); delay(50);
  }


  for (int j = 0 ; j < 2; j++)
  {
    pinMode(pwm[j], OUTPUT); delay(50);
  }
  //pinMode(0,OUTPUT);
  //pinMode(1,OUTPUT);
  //digitalWrite(0,HIGH);
  //digitalWrite(1,HIGH);
  digitalWrite(mpu[0], LOW); digitalWrite(mpu[1], LOW);
  digitalWrite(mpu[0], HIGH);
  Serial.print("l3l1    ");
  Serial.print(mpu[0]);
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {

    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = kfx11.updateEstimate(ax);
    az = kfy11.updateEstimate(az);
    float angle = 180 * atan2(ax, az) / PI;
    fb1 = 180 - abs(angle) - 5.5 ; // fb1=180- abs(angle) -5 ;
    avg1 = average(fb1, 0);
  }

  digitalWrite(mpu[0], LOW); digitalWrite(mpu[1], LOW);
  digitalWrite(mpu[1], HIGH);
  Serial.print("l3l2    ");
  Serial.print(mpu[1]);
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {

    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = kfx12.updateEstimate(ax);
    az = kfy12.updateEstimate(az);
    float angle = 180 * atan2(ax, az) / PI;
    fb2 =  abs(angle);
    fb2 = 180 - fb2;
    fb2 = fb2 - fb1;
    avg2 = average(fb2, 1);
  }
  digitalWrite(mpu[0], LOW);  digitalWrite(mpu[1], LOW);

  // initialize timer1
  delay(5000);
  noInterrupts();           // disable all interrupts

  TCCR1A = 0 ;
  TCCR1B = 0;

  TCNT1  = 0;

  OCR1A = 5000;            // compare match register 16MHz/256/2Hz

  TCCR1B |= (1 << WGM12);   // CTC mode

  TCCR1B |= (1 << CS12);    // 256 prescalerp
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  //  Serial.print("noint");
  interrupts();             // enable all interrupts
  Serial.println("Set points");
  gotopos(points[0][0], points[0][1]);
}

void loop() {
  // put your main code here, to run repeatedly:
  chosen_fun();
  check_point(); // yet to decide whether to call in loop or ISR ---- not decided

}

void gotopos(volatile float _X, volatile  float _Y)
{
  // Serial.println(" ");
  X = _X;
  Y = _Y;
  flag[0] = 1;
  flag[1] = 1;
}
void chosen_fun()
{
  if  (neg_flag == 1)
  {
    calculate_neg_angle(X, Y);
    neg_flag = 0;
  }
  if  (pos_flag == 1)
  {
    calculate_pos_angle(X, Y);
    pos_flag = 0;
  }
}


//*************************//
//choose function

void choose_fn()
{
  if (X < 0)
  {
    Serial.print(" flag 1 "); Serial.print(flag[0]  );   Serial.print("    flag 2   "); Serial.print(flag[1]);// Serial.print("    leg   "); Serial.print(leg);

    if (flag[0] == 1 || flag[1] == 1)
    {
      neg_flag = 1;
    }
  }
  else if (X > 0)
  {
    if (flag[0] == 1 || flag[1] == 1)
    {
      pos_flag = 1;
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
  T[0] = phi2 - phi1;
  phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
  T[1] = pi - phi3;
  T[0] = T[0] * 180 / pi;
  T[1] = T[1] * 180 / pi;
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
  T[0] = phi2 - phi1;
  phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
  T[1] = pi - phi3;
  T[0] = T[0] * 180 / pi;
  T[1] = T[1] * 180 / pi;
  onoffcontrol();
}
//*************************//
//control logic for motion

void onoffcontrol()
{

  float angle;
  //Read the feedback pot
  digitalWrite(mpu[1], LOW);  digitalWrite(mpu[0], LOW);
  digitalWrite(mpu[0], HIGH);
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  Serial.print("#####################################leg   ");

  Serial.print("X in class    "); Serial.print(X); Serial.print("        Y in class    ");
  Serial.print(Y);
  ax = kfx11.updateEstimate(ax);
  az = kfy11.updateEstimate(az);
  Serial.print("Link 1   angle=   ");
  angle = 180 * atan2(ax, az) / PI;
  fb1 = 180 - abs(angle) - 5.5 + 3 ;

  Serial.print(fb1);
  avg1 = average(fb1, 0);
  Serial.print("   ");
  Serial.print(T[0]);

  digitalWrite(mpu[1], LOW);  digitalWrite(mpu[0], LOW);
  digitalWrite(mpu[1], HIGH);
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  ax = kfx12.updateEstimate(ax);
  az = kfy12.updateEstimate(az);
  Serial.print("Link2   angle=");
  Serial.print(" ");
  angle = 180 * atan2(ax, az) / PI;
  fb2 =  abs(angle) + 1;
  fb2 = 180 - fb2;
  fb2 = fb2 - fb1;
  Serial.print(fb2);
  Serial.print(" ");
  Serial.println(T[1]);
  Serial.print(" ");
  avg2 = average(fb2, 1);
  Serial.println(avg1);
  Serial.println(avg2);
  fb1 = avg1;
  fb2 = avg2;
  digitalWrite(mpu[1], LOW);
  digitalWrite(mpu[1], LOW);  digitalWrite(mpu[0], LOW);
  //      //Find error
  error1 = T[0] - fb1;
  error2 = T[1] - fb2;

  analogWrite(pwm[0], 150); //pwm1);
  analogWrite(pwm[1], 150); //);


  if ((error1) <= 5 && (error1) >=  -5 )
  {
    analogWrite(pwm[0], 0);
    hardstop(brake[0]);
    flag[0] = 0;
    Serial.print(pwm[0]);
    Serial.println("L1 stop");
  }
  else
  {
    flag[0] = 1;
    Serial.println("L1 start");

  }
  if ((error2) <= 5 && (error2) >= -5 )
  {
    analogWrite(pwm[1], 0);
    hardstop(brake[1]);
    flag[1] = 0;
    Serial.print(pwm[1]);
    Serial.println("L2 stop");
  }
  else
  {
    flag[1] = 1;
    Serial.println("L2 start");
  }

  if (fb1 < T[0] && fb2 < T[1])
  {
    if (flag[0] == 1)
    {
      backward(dir[0], brake[0]);
      Serial.print("link one increase angle"); Serial.print(" "); Serial.print (dir[0]); Serial.print(" "); Serial.print (dir[1]);
    }
    if (flag[1] == 1)
    {
      forward(dir[1], brake[1]);
      Serial.print("link two  increase angle"); Serial.print(" "); Serial.print (dir[2]); Serial.print(" "); Serial.print (dir[3]);
    }
  }
  else if (fb1 < T[0] && fb2 > T[1])
  {
    if (flag[0] == 1)
    {
      //          forward(dir[0], dir[1]);
      backward(dir[0], brake[0]);
      Serial.print("link one  increase angle"); Serial.print(" "); Serial.print (dir[0]); Serial.print(" "); Serial.print (dir[1]);
    }
    if (flag[1] == 1)
    {
      backward(dir[1],  brake[1]);
      Serial.print("link two decrease angle"); Serial.print(" "); Serial.print (dir[2]); Serial.print(" "); Serial.print (dir[3]);
    }
  }
  else if (fb1 > T[0] && fb2 < T[1])
  {
    if (flag[0] == 1)
    {
      //          backward(dir[0], dir[1]);
      forward(dir[0], brake[0]);
      Serial.print("link one decrease angle"); Serial.print(" "); Serial.print (dir[0]); Serial.print(" "); Serial.print (dir[1]);
    }
    if (flag[1] == 1)
    {
      forward(dir[1], brake[1]);

      Serial.print("link two  increase angle"); Serial.print(" "); Serial.print (dir[2]); Serial.print(" "); Serial.print (dir[3]);
    }
  }
  else if (fb1 > T[0]  && fb2 > T[1])
  {
    if (flag[0] == 1)
    {
      //          backward(dir[0], dir[1]);
      forward(dir[0], brake[0]);
      Serial.print("link one decrease angle"); Serial.print(" "); Serial.print (dir[0]); Serial.print(" "); Serial.print (dir[1]);
    }
    if (flag[1] == 1)
    {
      backward(dir[1], brake[1]);
      Serial.print("link two  decrease angle"); Serial.print(" "); Serial.print (dir[2]); Serial.print(" "); Serial.print (dir[3]);
    }
  }
  Serial.print("flag");
  Serial.print(flag[0]);
  Serial.println(flag[1]);
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
}//mega

//*************************//
//ISR

SIGNAL(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  Serial.println("ISR");
  cli();
  OCR1A = 1000;
  choose_fn();
  //check_point();
  sei();

}

void check_point()
{
  Serial.print(flag[0]);
  Serial.print("\t");
  Serial.print(flag[1]);
  Serial.print("\t");
  Serial.println(pointer);
  if (flag[0] == 0 && flag[1] == 0)
  {
    Serial.write(2);
    //digitalWrite(0, LOW);

    Serial.println(flag[0]);
    Serial.println(flag[1]);
    //pointer = pointer + 1;
    if (pointer > 3)
    {
      pointer = 0;
    }
    gotopos(points[pointer][0], points[pointer][1]);
  }
  else
  {
    //digitalWrite(0, HIGH); Serial.write(1);
    gotopos(points[pointer][0], points[pointer][1]);
  }
  /*if (digitalRead(1) == HIGH)
    {
    pointer = pointer + 1;
    if (pointer > 3)
    {
      pointer = 0;
    }
    gotopos(points[pointer][0], points[pointer][1]);
    //char pointer = //Serial.read();
    Serial.println("//Serial available");
    //pointer=pointer+1;
    //Serial.print("Points ( . )( . )");
    //Serial.print("\t");
    //Serial.print(points[int(pointer)][0]);
    //Serial.println(points[int(pointer)][1]);
    }
    else
    {
    gotopos(points[pointer][0], points[pointer][1]);
    }*/
}//uno
