//Declaring all the variables

float pi = 3.14159;
float a1 = 0;
float a2 = 39;
float a3 = 0;
float a4 = 39;
int relay[4][4] = {{23, 25, 27, 29}, {31, 33, 35, 37}, {39, 41, 43, 45}, {47, 49, 51, 53}};
float T[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
bool flag_leg[4][2] = {{1, 1}, {1, 1}, {1, 1}, {1, 1}};//{{0, 0}, {0, 0}, {0, 0}, {0, 0}};
float mode[4] = {0, 0, 0, 0};
///////////////////////
//constants here
float points[6][2] = {{0, 0}, {5.5, 0}, {11, 0}, {9, 2.7}, {5.5, 5}, {2, 2.7}};
int x_bias = 10;
int y_bias = 50;
int pointer[4] = {1, 4, 1, 4};
///////////////////////
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
          //leg0.gotopos(points[leg][0], points[leg][1]);
          Serial.print("leg 0 points ");
          Serial.print(points[pointer[0]][0]);
          Serial.print("  ");
          Serial.println(points[pointer[0]][1]);
          pointer[0]++;
          if (pointer[0] > 5)
            pointer[0] = 0;
        }
      }
      else if (leg == 1)
      {
        if (flag_leg[leg][0] == 1 && flag_leg[leg][1] == 1)
        {
          //leg1.gotopos(points[leg][0], points[leg][1]);
          Serial.print("leg 1 points ");
          Serial.print(points[pointer[1]][0]);
          Serial.print("  ");
          Serial.println(points[pointer[1]][1]);
          pointer[1]++;
          if (pointer[1] > 5)
            pointer[1] = 0;
        }
      }
      else if (leg == 2)
      {
        if (flag_leg[leg][0] == 1 && flag_leg[leg][1] == 1)
        {
          //leg2.gotopos(points[leg][0], points[leg][1]);
          Serial.print("leg 2 points ");
          Serial.print(points[pointer[2]][0]);
          Serial.print("  ");
          Serial.println(points[pointer[2]][1]);
          pointer[2]++;
          if (pointer[2] > 5)
            pointer[2] = 0;
        }
      }
      else if (leg == 3)
      {
        if (flag_leg[leg][0] == 1 && flag_leg[leg][1] == 1)
        {
          //leg3.gotopos(points[leg][0], points[leg][1]);
          Serial.print("leg 3 points ");
          Serial.print(points[pointer[3]][0]);
          Serial.print("  ");
          Serial.println(points[pointer[3]][1]);
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

void setup() {
  // put your setup code here, to run once:
  //int Time = millis();

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
  //*************************//
  path0.givePath();
  path1.givePath();
  path2.givePath();
  path3.givePath();
}

void loop() {
  // put your main code here, to run repeatedly:
  

}
