// this code is for driver recieved from robukits having direction pin ,brake pin , and pwm pin
//Include all libraries
#include <Thread.h>
#include <ThreadController.h>

volatile int a = 0;
/**********************************************/

int e_mea = 1;
float angle;
int e_est = 1;
int q = 1 ;
int l = 0, m = 1, n = 2, o = 3;

/*communication details************************************/
int c_mpu_number = 0;
const char startOfNumberDelimiter = '<';
const char endOfNumberDelimiter   = '>';
int pitch_c[8] = {0, 0, 0, 0, 0, 0, 0, 0};





/**********************************************/
//Declare constants for mpu
int16_t ax, ay, az;
int16_t gx, gy, gz;

//Declaring all the variables

//constant varibales 
const float pi = 3.14159;
const float a1 = 0;
const float a2 = 39;
const float a3 = 0;
const float a4 = 39;
//
float fb1 , fb2;
//volatile
const int  no_pointer = 4;
int pwm[4][2] = {{13, 12}, {11, 10}, {9, 8}, {7, 6}};
int driver[4][2] = {{25, 29}, {33, 37}, {41, 45}, {49, 53}}; //50 KA 51,48 KA 49
int mpu [4][2] = {{0 , 1}, {2, 3}, {4, 5}, {6, 7}}; 
int brake[4][2] = {{23, 27}, {31, 35}, {39, 43}, {47, 51}}; //51 KA 50,49 KA 48
float T[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
volatile int flag[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
volatile int neg_flag[4] = {0, 0, 0, 0};
volatile int pos_flag[4] = {0, 0, 0, 0};
int pointer [4] = {0, 0, 0, 0};


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

//Thread declaration
Thread leg_thread = Thread();
Thread communication_thread = Thread();

ThreadController all_thread = ThreadController();

//volatile float points[10][2] = {/*{0, 55.15}, { 0 , 54.15}, { 0, 53.15}, { 0, 52.15}, { 0, 51.15},*/ { 0, 50.15}, { -6, 51.15}, { -8, 52.15}, { -9.17, 53.15}, { -9.8, 54.15}, { -10, 55.15}, { -9.8, 56.15}, { -9.17, 57.15}, { -8, 58.15}, { -6, 59.15}};
//volatile float points[36][2] = { { 0, 55.15}, { 0, 54.15}, { 0, 53.15}, { 0, 52.15}, { 0, 51.15}, { 0, 50.15}, { -6, 51.15}, { -8, 52.15}, { -9.17, 53.15}, { -9.8, 54.15},{-10, 55.15},{ -9, 55.15},{-8,55.15},{-7,55.15},{-6,55.15},{-5,55.15},{-4,55.15},{-3,55.15},{-2,55.15},{-1,55.15},{0,55.15},{1,55.15},{2,55.15},{3,55.15},{4,55.15},{5,55.15},{6,55.15},{7,55.15},{8,55.15},{9,55.15},{10,55.15},{9.8,54.15},{9.17,53.15},{8,52.15},{6,51.15},{0.50.15} };
//volatile
//volatile int pointer1 = 0,pointer2 = 0,pointer3 = 0,pointer4 = 0;
/*****************************************************************************************************************************/

class Leg
{
  public:
    volatile int leg;  //private variable for leg number
    volatile float X;
    volatile float Y;

    volatile float points[no_pointer][2];


    int readIndex[2] = {0, 0};
    int total[2] = {0, 0};

    int numReadings = 10;
    int readings[2][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    float  avg1, avg2;
    float fb2 = 0, fb1 = 0;
    float error1 = 0;
    float error2 = 0;
    Leg(int _leg, volatile float _points[no_pointer][2])
    {
      leg = _leg; //declare public variable
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
      X = _X;
      Y = _Y;
      flag[leg][0] = 1;
      flag[leg][1] = 1;
    }
    void chosen_fun()
    {
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
      if (X < 0)
      {
        Serial.print(" flag 1 "); Serial.print(flag[leg][0]  );   Serial.print("    flag 2   "); Serial.print(flag[leg][1]);// Serial.print("    leg   "); Serial.print(leg);
        if (flag[leg][0] == 1 || flag[leg][1] == 1)
        {
          neg_flag[leg] = 1;
        }
      }
      else if (X > 0)
      {
        if (flag[leg][0] == 1 || flag[leg][1] == 1)
        {
          pos_flag[leg] = 1;
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
      T[leg][0] = phi2 - phi1;
      phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
      T[leg][1] = pi - phi3;
      T[leg][0] = T[leg][0] * 180 / pi;
      T[leg][1] = T[leg][1] * 180 / pi;
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
      onoffcontrol();
    }
    //*************************//
    //control logic for motion

    void onoffcontrol()
    {
      float Kp1 = 1.3, Kp2 = 45;
      int standard = 150;
      String temp;
      //Read the feedback pot
      angle=pitch_c[mpu[leg][0]];
      fb1 = 180 - abs(angle) - 5.5 ;
      Serial.print(fb1);
      avg1 = average(fb1, 0);
      angle = pitch_c[mpu[leg][1]];
      fb2 = angle;
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
      error1 = T[leg][0] - fb1;
      error2 = T[leg][1] - fb2;
      int pwm1 = (abs(error1) - abs(error2)) * Kp1 + standard;
      int pwm2 = 255;
      /* the commented sketch is for manupalting the speeds of the actuators according to the 
      //      int pwm1 = int((error1) * Kp1 * (abs(error1) - abs(error2)) + standard);
      //      int pwm2 = int((error2) * Kp2 * (pow(1.7, (-abs(error1) + 20)) + 1) + standard);
      pwm1 = constrain(pwm1, 0, 255);
      //      pwm2 = constrain(pwm2, 0, 255);
      */

      analogWrite(pwm[leg][0], 255); 
      analogWrite(pwm[leg][1], 255); 
      //Control statements for feedback based motion
      if ((error1) <= 5 && (error1) >=  -5 )
      {
        
        analogWrite(pwm[leg][0], 0);
        hardstop(brake[leg][0]);
        flag[leg][0] = 0;
        Serial.print(pwm[leg][0]);
        Serial.println("L1 stop");
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
      {
        pointer[leg] = pointer[leg] + 1;
        if (pointer[leg] == no_pointer  )
        {
          pointer[leg] = 0;
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
Leg leg1 = Leg(0,  points_leg1);
Leg leg2 = Leg(1,  points_leg2);
Leg leg3 = Leg(2,  points_leg3);
Leg leg4 = Leg(3,  points_leg4);


//Setup function to setup baud rate pinModes

void setup()
{
  
  Serial.begin(9600);
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
  
  Serial.print(" "); Serial.print(mpu[0][0]); Serial.print(" "); Serial.print(mpu[0][1]); Serial.print(" "); Serial.print(mpu[1][0]); Serial.print(" "); Serial.print(mpu[1][1]);
  delay(5000);
  Serial.println("start");
  
  //threads reqd
  leg_thread.onRun(t_tread);
  leg_thread.setInterval(100); // for now its 100 milliseconds
  communication_thread.onRun(processInput_c);
  communication_thread.setInterval(10);

  all_thread.add(leg_thread);
  all_thread.add(communication_thread);
  
  

  Serial.println("Set points");

  leg1.gotopos(20, 60);
  leg2.gotopos(20, 60);
  leg3.gotopos(20, 60);
  leg4.gotopos(20, 60);
  Serial.println("done with this ");
}
/*
SIGNAL(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  Serial.println("ISR");
  cli();
  OCR1A = 5000;

  leg1.choose_fn();
  leg2.choose_fn();
  leg3.choose_fn();
  leg4.choose_fn();

    if  (/*flag[0][0] == 0 && flag[0][1] == 0 )*//*&& flag[1][0] == 0 && flag[1][1] == 0  //&&flag[2][0] == 0 && flag[2][1] == 0 )//&& flag[3][0] == 0 && flag[3][1] == 0 )
  /*Serial.println("*#*#*#*#*#*#*#*");
  Serial.print(flag[1][0]);
  Serial.print("    ");
  Serial.println(flag[1][1]);
  if  ( flag[0][0] == 0 && flag[0][1] == 0 && flag[1][0] == 0 && flag[1][1] == 0 && flag[2][0] == 0 && flag[2][1] == 0 && flag[3][0] == 0 && flag[3][1] == 0 )
  {
    Serial.println("Passed Condition");
    leg1.check_point();
    leg2.check_point();
    leg3.check_point();
    leg4.check_point();
  }
  sei();

}*/

void t_tread()
{
  leg1.choose_fn();
  leg2.choose_fn();
  leg3.choose_fn();
  leg4.choose_fn();

 if( flag[0][0] == 0 && flag[0][1] == 0 && flag[1][0] == 0 && flag[1][1] == 0 && flag[2][0] == 0 && flag[2][1] == 0 && flag[3][0] == 0 && flag[3][1] == 0 )
  {
    Serial.println("Passed Condition");
    leg1.check_point();
    leg2.check_point();
    leg3.check_point();
    leg4.check_point();
    
  }
}

//*********communication function     ****************//
void processInput_c ()
{
  while(Serial.available()){
  static long receivedNumber = 0;
  static boolean negative = false;
  byte c = Serial.read ();
  switch (c)
  {
    case endOfNumberDelimiter:
      if (negative)
      {
        pitch_c[c_mpu_number] = -receivedNumber;
      }
      else
      {
        pitch_c[c_mpu_number] = receivedNumber;
      }
      break;
    // fall through to start a new number
    case startOfNumberDelimiter:
      receivedNumber = 0;
      negative = false;
      break;

    case '-':
      negative = true;
      break;

    case '0' :    case '1':    case '2':    case '3':    case '4':    case '5':    case '6':    case '7':    case '8':    case '9':
      receivedNumber *= 10;
      receivedNumber += c - '0';
      break;

    case ':' :
      c_mpu_number = receivedNumber;
      receivedNumber = 0;
      break;
   }
  }
}




//loop function
void loop()
{
  Serial.println("LOOPLOOPLOOPLOOPLOOPLOOP");
  leg1.chosen_fun();
  leg2.chosen_fun();
  leg3.chosen_fun();
  leg4.chosen_fun();
  all_thread.run();
  
}
