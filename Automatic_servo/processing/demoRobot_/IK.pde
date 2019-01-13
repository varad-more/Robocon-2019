//Declaring all the variables

float pi = 3.14159;
float a1 = 0;
float a2 = 39;
float a3 = 0;
float a4 = 39;
int relay[][] = {{23, 25, 27, 29}, {31, 33, 35, 37}, {39, 41, 43, 45}, {47, 49, 51, 53}};
float T[][] = {{4, pi - 1}, {0, 0}, {0, 0}, {0, 0}};
int flag[][] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
float millisOld, gTime, gSpeed = 4;

//*****************************************************************************************************************************//
int leg = 0;  //private variable for leg number
float X;
float Y;

//gotopos takes X and Y and Goes to that position

void gotopos(float _X, float _Y)
{
  X = _X;
  Y = _Y;
  setTime();
  flag[0][leg] = 1;
  flag[1][leg] = 1;
}
//*************************//
//choose function

void choose_fn()
{
  if (X < 0)
  {
    if (flag[0][leg] == 1 || flag[1][leg] == 1)
    {
      calculate_neg_angle(X, Y);
    }
  } else
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
  //T[0][leg] = T[0][leg] * 180 / pi;
  //T[1][leg] = T[1][leg] * 180 / pi;
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
  T[0][leg] = phi2 - phi1;
  phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
  T[1][leg] = pi - phi3;
  //T[0][leg] = T[0][leg] * 180 / pi;
  //T[1][leg] = T[1][leg] * 180 / pi;
}
//*************************//
void setTime() {
  gTime += ((float)millis()/1000 - millisOld)*(gSpeed/4);
  if (gTime >= 4)  gTime = 0;  
  millisOld = (float)millis()/1000;
  choose_fn();
}

//*****************************************************************************************************************************//
