//Declaring all the variables

float pi = 3.14159;
float a1 = 0;
float a2 = 39;
float a3 = 0;
float a4 = 39;
int relay[4][4] = {{23, 25, 27, 29}, {31, 33, 35, 37}, {39, 41, 43, 45}, {47, 49, 51, 53}};
float T[][4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
bool flag_leg[][4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
float mode[4] = {0, 0, 0, 0};
float state_walk[][4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};

///////////////////////
//constants here
float points[6][2] = {{0, 0}, {5.5, 0}, {11, 0}, {9, 2.7}, {5.5, 5}, {2, 2.7}};
int x_bias = 10;
int y_bias = 50;
int pointer[4] = {1, 4, 1, 4};
///////////////////////
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

    void gotopos(float X_, float Y_)
    {
      X = X_;
      Y = Y_;
      flag_leg[0][leg] = 1;
      flag_leg[1][leg] = 1;
    }
    //*************************//
    //choose function

    void choose_fn()
    {
      if (X < 0)
      {
        if (flag_leg[0][leg] == 1 || flag_leg[1][leg] == 1)
        {
          calculate_neg_angle(X, Y);
        }
      }
      else
      {
        if (flag_leg[0][leg] == 1 || flag_leg[1][leg] == 1)
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
      T[0][leg] = T[0][leg] * 180 / pi;
      T[1][leg] = T[1][leg] * 180 / pi;
      onoffcontrol();
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
        fb1 = map(fb1, 831, 953, 115, 10);  //953,917,873,831

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
        fb2 = map(fb2, 916, 278, 165, 10);  //278,465,863,892,916

      //Find error
      error1 = T[0][leg] - fb1;
      error2 = T[1][leg] - fb2;

      //Control statements for feedback based motion
      if (abs(error1) < 2)
      {
        hardstop(relay[leg][0], relay[leg][1]);
        flag_leg[0][leg] = 0;
      }
      if (abs(error2) < 2)
      {
        hardstop(relay[leg][2], relay[leg][3]);
        flag_leg[1][leg] = 0;
      }

      if (fb1 < T[0][leg] && fb2 < T[1][leg])
      {
        if (flag_leg[0][leg] == 1)
          forward(relay[leg][0], relay[leg][1]);
        if (flag_leg[1][leg] == 1)
          forward(relay[leg][2], relay[leg][3]);
      }
      else if (fb1 < T[0][leg] && fb2 > T[1][leg])
      {
        if (flag_leg[0][leg] == 1)
          forward(relay[leg][0], relay[leg][1]);
        if (flag_leg[1][leg] == 1)
          backward(relay[leg][2], relay[leg][3]);
      }
      else if (fb1 > T[0][leg] && fb2 < T[1][leg])
      {
        if (flag_leg[0][leg] == 1)
          backward(relay[leg][0], relay[leg][1]);
        if (flag_leg[1][leg] == 1)
          forward(relay[leg][2], relay[leg][3]);
      }
      else if (fb1 > T[0][leg]  && fb2 > T[1][leg])
      {
        if (flag_leg[0][leg] == 1)
          backward(relay[leg][0], relay[leg][1]);
        if (flag_leg[1][leg] == 1)
          backward(relay[leg][2], relay[leg][3]);
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
};


Leg leg0 = Leg(0);
Leg leg1 = Leg(1);
Leg leg2 = Leg(2);
Leg leg3 = Leg(3);

class walkGait
{
    //Declare constants
    int diff;
    int leg;
    float X;
    float Y;
  public:
    walkGait(int _leg)
    {
      leg = _leg;
    }
    //*************************//
    //decide path either sine or line
    void givePath()
    {
      move_leg(leg);
    }
    //*************************//
    //choose function

    void move_leg(int leg)
    {
      //check if previous point reached
      if (leg == 0)
      {
        if (flag_leg[leg][0] == 1 && flag_leg[leg][1] == 1)
        {
          leg0.gotopos(points[leg][0], points[leg][1]);
          //Serial.print("leg 0 points ");
          //Serial.print(points[pointer[0]][0]);
          //Serial.print("  ");
          //Serial.println(points[pointer[0]][1]);
          pointer[0]++;
          if (pointer[0] > 5)
            pointer[0] = 0;
        }
      }
      else if (leg == 1)
      {
        if (flag_leg[leg][0] == 1 && flag_leg[leg][1] == 1)
        {
          leg1.gotopos(points[leg][0], points[leg][1]);
          //Serial.print("leg 1 points ");
          //Serial.print(points[pointer[1]][0]);
          //Serial.print("  ");
          //Serial.println(points[pointer[1]][1]);
          pointer[1]++;
          if (pointer[1] > 5)
            pointer[1] = 0;
        }
      }
      else if (leg == 2)
      {
        if (flag_leg[leg][0] == 1 && flag_leg[leg][1] == 1)
        {
          leg2.gotopos(points[leg][0], points[leg][1]);
          //Serial.print("leg 2 points ");
          //Serial.print(points[pointer[2]][0]);
          //Serial.print("  ");
          //Serial.println(points[pointer[2]][1]);
          pointer[2]++;
          if (pointer[2] > 5)
            pointer[2] = 0;
        }
      }
      else if (leg == 3)
      {
        if (flag_leg[leg][0] == 1 && flag_leg[leg][1] == 1)
        {
          leg3.gotopos(points[leg][0], points[leg][1]);
          //Serial.print("leg 3 points ");
          //Serial.print(points[pointer[3]][0]);
          //Serial.print("  ");
          //Serial.println(points[pointer[3]][1]);
          pointer[3]++;
          if (pointer[3] > 5)
            pointer[3] = 0;
        }
      }
    }
};
//*****************************************************************************************************************************//

walkGait path0 = walkGait(0);
walkGait path1 = walkGait(1);
walkGait path2 = walkGait(2);
walkGait path3 = walkGait(3);

//Setup function to setup baud rate pinModes

void setup()
{
  int Time = millis();

  Serial.begin(115200);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

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

  noInterrupts();
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
  interrupts();
}
//*************************//
//ISR

SIGNAL(TIMER0_COMPA_vect)
{
  leg0.choose_fn();
  leg1.choose_fn();
  leg2.choose_fn();
  leg3.choose_fn();
  //*************************//
  path0.givePath();
  path1.givePath();
  path2.givePath();
  path3.givePath();
}
//*************************//
//loop function

void loop()
{

}
//*************************//
