#include<Servo.h>

Servo s1;
Servo s2;

float pi = 3.14159;
float r1 = 0;
float phi1 = 0;
float phi2 = 0;
float phi3 = 0;
float a1 = 0;
float a2 = 5;
float a3 = 0;
float a4 = 4;
float T1 = 0;
float T2 = 0;
float X = 5;
float Y = 7;

void setup() {
  Serial.begin(115200);

  s1.attach(9);
  s2.attach(10);

  s1.write(0);
  s2.write(0);

  r1 = sqrt(X * X + Y * Y);
  phi1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
  phi2 = atan(Y / X);
  T1 = phi2 - phi1;
  phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
  T2 = pi - phi3;

  T1 = T1 * 180 / pi;
  T2 = T2 * 180 / pi;

  delay(1000);
  
  Serial.print("T1  ");
  Serial.println(T1);
  Serial.print("T2  ");
  Serial.println(T2);

  T1 = map(T1,0,90,90,0);
  T2 = map(T1,0,180,180,0);
  
  if (T1 < 90)
  {
    s1.write(T1);
  }
  if (T2 < 180)
  {
    s2.write(T2);
  }
}

void loop() {

}
