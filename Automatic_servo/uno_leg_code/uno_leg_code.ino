#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "MegunoLink.h"
#include "SimpleKalmanFilter.h"
MPU6050 accelgyro(0x69);
#define e_mea 1
#define e_est 1
#define q 1
#define link1 0
#define link2 1
#define pwm_link1  0
#define pwm_link2  0
#define  driver_link1  0
#define driver_link2   0
#define brake_link1  0
#define brake_link2  0
#define mpu_link1  0
#define mpu_link2  0
class Leg
{
  public:
    float X, Y;
    SimpleKalmanFilter kfx1 = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfy1 = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfx2 = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfy2 = SimpleKalmanFilter(e_mea, e_est, q);
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    float points[4][2] = { {20, 60}, { -20, 60}, {20, 60}, { -20, 60}};
    int pwm[2] = {pwm_link1, pwm_link2};
    int driver[2] = { driver_link1, driver_link2};
    int brake[2] = { brake_link1, brake_link2};
    int mpu [2] = {mpu_link1, mpu_link2};
    float error[2] = {0, 0};
    int flag[2] = {0, 0};
    int neg_flag = 0;
    int pos_flag = 0;
    int pointer = 0;
    float fb1;
    int T[2] = {0, 0};
    Leg()
    {
      while (!Serial.available());
      pointer = Serial.read();
    }
    void gotopos(float _X, float _Y)
    {
      X = _X;
      Y = _Y;
      flag [link1] = 1;
      flag [link2] = 1;
    }
    void chosen_fun()
    {
      if  (neg_flag == 1)
      {
        calculate_neg_angle(X, Y);
        neg_flag  = 0;
      }
      if  (pos_flag  == 1)
      {
        calculate_pos_angle(X, Y);
        pos_flag  = 0;
      }
    }
    void choose_fn()
    {
      if (X < 0)
      {
        Serial.print(" flag 1 "); Serial.print(flag  [link1]  );   Serial.print("    flag 2   "); Serial.print(flag  [link2]);
        if (flag  [link1] == 1 || flag  [link2] == 1)
        {
          neg_flag  = 1;
        }
      }
      else if (X > 0)
      {
        if (flag  [link1] == 1 || flag  [link2] == 1)
        {
          pos_flag  = 1;
        }
      }
      else
      {
        Serial.println("  gotopos not set");
      }
    }
    void calculate_pos_angle(float X, float Y)
    {
      Serial.println("In positive");
      float r1 = 0;
      float phi1 = 0;
      float phi2 = 0;
      float phi3 = 0;
      float a2 = 39;
      float a4 = 39;
      r1 = sqrt(X * X + Y * Y);
      phi1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
      phi2 = atan(Y / X);
      T[link1] = phi2 - phi1;
      phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
      T[link2] = PI - phi3;
      T[link1] = T  [link1] * 180 / PI;
      T [link2] = T  [link2] * 180 / PI;
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
      float a2 = 39;
      float a4 = 39;
      X = abs(X);
      r1 = sqrt(X * X + Y * Y);
      phi1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
      phi2 = atan(-Y / X);
      phi2 = PI + phi2;
      T[link1] = phi2 - phi1;
      phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
      T[link2] = PI - phi3;
      T[link1] = T[link1] * 180 / PI;
      T[link2] = T[link2] * 180 / PI;
      onoffcontrol();
    }
    //*************************//
    //control logic for motion

    void onoffcontrol()
    { int angle, avg1, avg2, fb2, fb1;
      digitalWrite(mpu [link1], HIGH);
      digitalWrite(mpu [link2], LOW);
      accelgyro.initialize();
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
      Serial.print("X in class    "); Serial.print(X); Serial.print("        Y in class    ");
      Serial.print(Y);
      ax = kfx1.updateEstimate(ax);
      az = kfy1.updateEstimate(az);
      Serial.print("Link 1   angle=");
      angle = 180 * atan2(ax, az) / PI;
      fb1 = 180 - abs(angle) - 5.5 ;
      Serial.print(fb1);
      avg1 = average(fb1, link1);
      Serial.print("   ");
      Serial.print(T  [link1]);
      digitalWrite(mpu [link1], LOW);
      digitalWrite(mpu [link2], HIGH);
      accelgyro.initialize();
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
      ax = kfx2.updateEstimate(ax);
      az = kfy2.updateEstimate(az);
      Serial.print("Link2   angle=");
      Serial.print(" ");
      angle = 180 * atan2(ax, az) / PI;
      fb2 =  abs(angle);
      fb2 = 180 - fb2;
      fb2 = fb2 - fb1;
      Serial.print(fb2);
      Serial.print(" ");
      Serial.println(T[link2]);
      Serial.print(" ");
      avg2 = average(fb2, link2);
      Serial.println(avg1);
      Serial.println(avg2);
      fb1 = avg1;
      fb2 = avg2;

      digitalWrite(mpu [link1], LOW);
      digitalWrite(mpu [link2], LOW);
      //      //Find error
      error[link1] = T[link1] - fb1;
      error[link2] = T[link2] - fb2;
      analogWrite(pwm  [link1], 255); //pwm1);
      analogWrite(pwm  [link2], 255); //);
      //Control statements for feedback based motion
      if (( error[link1]) <= 5 && ( error[link1]) >=  -5 )
      {
        analogWrite(pwm[link1], 0);
        hardstop(brake[link1]);
        flag[link1] = 0;
        Serial.print(pwm[link1]);
        Serial.println("L1 stop");
      }
      else
      {
        flag[link1] = 1;
        Serial.println("L1 start");
      }
      if (( error[link2]) <= 5 && ( error[link2]) >= -5 )
      {
        analogWrite(pwm  [link2], 0);
        hardstop(brake  [link2]);
        flag  [link2] = 0;
        Serial.print(pwm  [link2]);
        Serial.println("L2 stop");
      }
      else
      {
        flag  [link2] = 1;
        Serial.println("L2 start");
      }

      if (fb1 < T  [link1] && fb2 < T  [link2])
      {
        if (flag  [link1] == 1)
        {
          backward(driver  [link1], brake  [link1]);
          Serial.print("link one increase angle"); Serial.print(" "); Serial.print (driver  [link1]); Serial.print(" "); Serial.print (driver  [link2]);
        }
        if (flag  [link2] == 1)
        {
          forward(driver  [link2], brake  [link2]);
          Serial.print("link two  increase angle"); Serial.print(" "); Serial.print (driver [2]); Serial.print(" "); Serial.print (driver [3]);
        }
      }
      else if (fb1 < T  [link1] && fb2 > T  [link2])
      {
        if (flag  [link1] == 1)
        {
          backward(driver  [link1], brake  [link1]);
          Serial.print("link one  increase angle"); Serial.print(" "); Serial.print (driver  [link1]); Serial.print(" "); Serial.print (driver  [link2]);
        }
        if (flag  [link2] == 1)
        {
          backward(driver  [link2],  brake  [link2]);
          Serial.print("link two decrease angle"); Serial.print(" "); Serial.print (driver [2]); Serial.print(" "); Serial.print (driver [3]);
        }
      }
      else if (fb1 > T  [link1] && fb2 < T  [link2])
      {
        if (flag  [link1] == 1)
        {
          forward(driver  [link1], brake  [link1]);
          Serial.print("link one decrease angle"); Serial.print(" "); Serial.print (driver  [link1]); Serial.print(" "); Serial.print (driver  [link2]);
        }
        if (flag  [link2] == 1)
        {
          forward(driver  [link2], brake  [link2]);
          Serial.print("link two  increase angle"); Serial.print(" "); Serial.print (driver [2]); Serial.print(" "); Serial.print (driver [3]);
        }
      }
      else if (fb1 > T[link1]  && fb2 > T[link2])
      {
        if (flag[link1] == 1)
        {
          //          backward(driver  [link1], driver  [link2]);
          forward(driver [link1], brake [link1]);
          Serial.print("link one decrease angle"); Serial.print(" "); Serial.print (driver  [link1]); Serial.print(" "); Serial.print (driver  [link2]);
        }
        if (flag [link2] == 1)
        {
          backward(driver[link2], brake [link2]);
          Serial.print("link two  decrease angle"); Serial.print(" "); Serial.print (driver [2]); Serial.print(" "); Serial.print (driver [3]);
        }
      }
      Serial.print("flag");
      Serial.print(flag [link1]);
      Serial.println(flag [link2]);
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
    float average(int val, int link)
    {
      static int readIndex[2] = {0, 0};
      static float total[2] = {0, 0};
      int numReadings = 10;
      static int readings[2][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
      total[link] = total[link] - readings[link][readIndex[link]];
      // read from the sensor:
      readings[link][readIndex[link]] = val;
      // add the reading to the total:
      total[link] = total[link] + readings[link][readIndex[link]];
      // advance to the next position in the array:
      readIndex[link] = readIndex[link] + 1;

      // if we're at the end of the array...
      if (readIndex[link] >= numReadings) {
        // ...wrap around to the beginning:
        readIndex[link] = 0;
      }
      // calculate the average:
      return (total[link] / (float)numReadings);
    }

    void update_mega()
    { //if the legs reached then  inform mega
      if (flag[link1] == 0 && flag[link2] == 0)
      {
        Serial.write(1);
      }
      else 
      {
        Serial.write(0);
      }
    }
    void update_pointer()
    { //check if mega sends next points rec
      if (Serial.available())
      {
        pointer = Serial.read();
        gotopos(points[pointer][0], points[pointer][1]);
      }
    }

    void initializempu()
    { //initialize mpu and average
      digitalWrite(mpu[link1], HIGH); digitalWrite(mpu[link2], LOW);
      accelgyro.initialize();
      Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
      for (int a = 0; a <= 9; a++)
      {
        float angle;
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        ax = kfx1.updateEstimate(ax);
        az = kfy1.updateEstimate(az);
        angle = 180 * atan2(ax, az) / PI;
        fb1 = 180 - abs(angle) - 5.5 ;
        average(fb1, link1);
      }
      digitalWrite(mpu[link1], LOW); digitalWrite(mpu[link2], HIGH);
      accelgyro.initialize();
      Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
      for (int a = 0; a <= 9; a++)
      {
        float fb2, angle;
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        ax = kfx2.updateEstimate(ax);
        az = kfy2.updateEstimate(az);
        angle = 180 * atan2(ax, az) / PI;
        fb2 =  abs(angle);
        fb2 = 180 - fb2;
        fb2 = fb2 - fb1;
        average(fb2, link2);
      }
      digitalWrite(mpu[link1], LOW); digitalWrite(mpu[link2], LOW);
    }
    void setup_pins()
    {
      //set all  input output pins
      for (int j = 0 ; j < 2; j++)
      {
        pinMode(driver[j], OUTPUT);
      }

      for (int j = 0; j < 2; j++)
      {
        pinMode(mpu[j], OUTPUT);
        digitalWrite(mpu[j], LOW);
        delay(10);
      }

      for (int j = 0; j < 2; j++)
      {
        pinMode(brake[j], OUTPUT);
      }
      for (int j = 0 ; j < 2; j++)
      {
        pinMode(pwm[j], OUTPUT);
      }

    }
};
Leg leg;

void setup() {
  // put your setup code here, to run once:
  leg.setup_pins();
  leg.initializempu();
  noInterrupts();           // disable all interrupts

  TCCR1A = 0 ;

  TCCR1B = 0;

  TCNT1  = 0;

  OCR1A = 3000;            // compare match register 16MHz/256/2Hz

  TCCR1B |= (1 << WGM12);   // CTC mode

  TCCR1B |= (1 << CS12);    // 256 prescaler

  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();
}
SIGNAL(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  cli();
  OCR1A = 3000;
  leg.choose_fn();
  leg.update_mega();
  leg.update_pointer();
  sei();
}

void loop() {
  // put your main code here, to run repeatedly:
  leg.chosen_fun();
  //leg.onoffcontrol();
}
