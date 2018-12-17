//Coded by Abhijit

float pi = 3.14159;
float r1 = 0;
float phi1 = 0;
float phi2 = 0;
float phi3 = 0;
float a1 = 0;
float a2 = 39;
float a3 = 0;
float a4 = 39;
float T1 = 0;
float T2 = 0;
float X = 0;
float Y = 0;
float fb1 = 0;
float fb2 = 0;
float Kp = 1;
float error1 = 0;
float error2 = 0;
bool flag1 = 1;
bool flag2 = 1;

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

void loop()
{
  //  T1 = 175;
  //  T2 = -90;
  X = 2 0;
  Y = 40;
  gotopos();
  
}


void gotopos()
{
  flag1 = 1;
  flag2 = 1;
  while (flag1 == 1 || flag2 == 1)
  {
    calculateangle();
    onoffcontrol();
  }
}
void calculateangle()
{
  r1 = sqrt(X * X + Y * Y);
  phi1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
  phi2 = atan(Y / X);
  T1 = phi2 + phi1;
  phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
  T2 = pi + phi3;

  T1 = T1 * 180 / pi;
  T2 = T2 * 180 / pi;

  T2 = T2 - 360;
}


void onoffcontrol()
{
  fb1 = analogRead(A0);
  fb2 = analogRead(A1);

  fb1 = map(fb1, 753, 139, 75, 170);
  fb2 = map(fb2, 110, 858, -160, 15);

  Serial.print("  fb1  ");
  Serial.print(fb1);
  Serial.print("  T1  ");
  Serial.print(T1);
  Serial.print("  fb2  ");
  Serial.print(fb2);
  Serial.print("  T2  ");
  Serial.print(T2);

  error1 = T1 - fb1;
  error2 = T2 - fb2;

  if (abs(error1) < 1)
  {
    hardstop(4, 5);
    flag1 = 0;
  }
  if (abs(error2) < 1)
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

