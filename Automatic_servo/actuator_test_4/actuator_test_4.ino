//Declaring all the variables

float pi = 3.14159;
float a1 = 0;
float a2 = 39;
float a3 = 0;
float a4 = 39;
float T1 = 0;
float T2 = 0;
bool flag1 = 1;
bool flag2 = 1;
//*************************//
//Setup function to setup baud rate pinModes

void setup()
{
  Serial.begin(115200);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  Serial.flush();
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
}
//*************************//
//loop function

void loop()
{
  gotopos(-10, 40);
}
//*************************//
//gotopos takes X and Y and Goes to that position

void gotopos(float X, float Y)
{
  flag1 = 1;
  flag2 = 1;
  if (X < 0)
  {
    while (flag1 == 1 || flag2 == 1)
    {
      calculate_neg_angle(X, Y);
      onoffcontrol(X, Y);
    }
  }
  else
  {
    while (flag1 == 1 || flag2 == 1)
    {
      calculate_pos_angle(X, Y);
      onoffcontrol(X, Y);
    }
  }
}
//*************************//
//calculates angle for positive X

void calculate_pos_angle(float X, float Y)
{
  float r1 = 0;
  float phi1 = 0;
  float phi2 = 0;
  float phi3 = 0;
  r1 = sqrt(X * X + Y * Y);
  phi1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
  phi2 = atan(Y / X);
  T1 = phi2 - phi1;
  phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
  T2 = pi - phi3;
  T1 = T1 * 180 / pi;
  T2 = T2 * 180 / pi;

}
//*************************//
//calculates angle for niggative X

void calculate_neg_angle(float X, float Y)
{
  float r1 = 0;
  float phi1 = 0;
  float phi2 = 0;
  float phi3 = 0;
  X = abs(X);
  r1 = sqrt(X * X + Y * Y);
  phi1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
  phi2 = atan(-Y / X);
  phi2 = pi + phi2;
  T1 = phi2 - phi1;
  phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
  T2 = pi - phi3;
  T1 = T1 * 180 / pi;
  T2 = T2 * 180 / pi;
}
//*************************//
//control logic for motion

void onoffcontrol(float X, float Y)
{
  //Read the feedback pot
  float fb1 = 0;
  float fb2 = 0;
  float error1 = 0;
  float error2 = 0;

  fb1 = analogRead(A0);
  fb2 = analogRead(A1);

  //Map pot1 to required range
  if (917 < fb1 && fb1 < 953)
    fb1 = map(fb1, 917, 953, 45, 10);
  else if (873 < fb1 && fb1 < 917)
    fb1 = map(fb1, 873, 917, 90, 45);
  else if (831 < fb1 && fb1 < 873)
    fb1 = map(fb1, 831, 873, 115, 90);
  else
    fb1 = map(fb1, 831, 953, 115, 10);

  //Map pot2 to required range
  if (278 < fb2 && fb2 < 465)
    fb2 = map(fb2, 278, 465, 10, 45);
  else if (465 < fb2 && fb2 < 863)
    fb2 = map(fb2, 465, 863, 45, 90);
  else if (863 < fb2 && fb2 < 892)
    fb2 = map(fb2, 863, 892, 90, 135);
  else if (892 < fb2 && fb2 < 916)
    fb2 = map(fb2, 892, 916, 135, 165);
  else
    fb2 = map(fb2, 916, 278, 165, 10);

  //Print statements for debugging
  Serial.print("  fb1  ");
  Serial.print(fb1);
  Serial.print("  T1  ");
  Serial.print(T1);
  Serial.print("  fb2  ");
  Serial.print(fb2);
  Serial.print("  T2  ");
  Serial.print(T2);

  //Find error
  error1 = T1 - fb1;
  error2 = T2 - fb2;

  //Control statements for feedback based motion
  if (abs(error1) < 1.5)
  {
    hardstop(4, 5);
    flag1 = 0;
  }
  if (abs(error2) < 1.5)
  {
    hardstop(6, 7);
    flag2 = 0;
  }

  if (fb1 < T1 && fb2 < T2)
  {
    if (flag1 == 1)
      forward(4, 5);
    if (flag2 == 1)
      forward(6, 7);

    Serial.println("  forward");
  }
  else if (fb1 < T1 && fb2 > T2)
  {
    if (flag1 == 1)
      forward(4, 5);
    if (flag2 == 1)
      backward(6, 7);

    Serial.println("  backward");
  }
  else if (fb1 > T1 && fb2 < T2)
  {
    if (flag1 == 1)
      backward(4, 5);
    if (flag2 == 1)
      forward(6, 7);

    Serial.println("  forward");
  }
  else if (fb1 > T1  && fb2 > T2)
  {
    if (flag1 == 1)
      backward(4, 5);
    if (flag2 == 1)
      backward(6, 7);

    Serial.println("  backward");
  }
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
