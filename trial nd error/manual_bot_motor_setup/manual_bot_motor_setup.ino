#include<PS2X_lib.h>
#include<math.h>
int m1pwm = 5;
int m2pwm = 13;
int m3pwm = 10;
int m1p1 = 6;
int m1p2 = 7;
int m2p1 = 12;
int m2p2 = 11;
int m3p1 = 8;
int m3p2 = 9;

void forward(int );
void backward(int );
void left (int );
void right(int );
void clock_wise(int);
void anti_clock_wise(int );
void hard_brake ( int );
void soft_brake();

PS2X p_stick ;
int p_stick_error = 0;
int p_stick_type = 0;
byte p_stick_vibrate = 0;
char stick_type = 0;

int* stick_values ( int stick_x, int stick_y);
int pwm_calc(int stick_y);

void setup() {
  pinMode(m1p1, OUTPUT);
  pinMode(m1p2, OUTPUT);
  pinMode(m2p1, OUTPUT);
  pinMode(m2p2, OUTPUT);
  pinMode(m3p1, OUTPUT);
  pinMode(m3p2, OUTPUT);

  //  hard_brake(255);

  Serial.begin(9600);
  p_stick_error = p_stick.config_gamepad(22, 4 , 3 , 23 , true, true); //setting the pins console on arduino  (clk,cmd,att,data,pres,rumble)
  if (p_stick_error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }

  else if (p_stick_error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (p_stick_error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else /*if (p_stick_error == 3)*/
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");


  stick_type = p_stick.readType();

}

//  Serial.println(diff_pwm(255)}

void loop() {
  /*right(100);
    delay(2000);
    hard_brake(100);
    delay(500);
  */
  int *stick;
  int x, y, pwm;
  p_stick.read_gamepad(false, p_stick_vibrate );
  x = p_stick.Analog(PSS_RX);
  y = p_stick.Analog(PSS_RY);
  //x = stick_x; y = stick_y;

  Serial.println(x);
  //Serial.print(" ");
  Serial.print(y);


  //stick = stick_values();
  //Serial.println(stick_y);
  //Serial.println(pwm);
  // Serial.println(stick[0], stick[1]);
  if (p_stick.Button(PSB_R3))
  {
    hard_brake(100);
  }

  if (p_stick.Button(PSB_L3))
  {
    soft_brake ();
  }


  if (x == 128 && y == 128)
  {
    soft_brake ();
  }
  if (x == 128 && (y >= 0 && y < 128) )
    //Serial.println(pwm);
  { int temp_pwm;
    temp_pwm = pwm_calc(y);
    if (temp_pwm > (-30))
    {
      pwm = 30 ;
    }
    else
    {
      pwm = temp_pwm;
    }
    Serial.println(" forward ");
    Serial.print(abs(pwm));
    forward(abs(pwm));
  }
  if (x == 128 && (y<=255 && y > 128) )
  {
    pwm = pwm_calc( y);
    Serial.println("backward ");
    Serial.print((pwm));
    backward ( pwm );
  }
  if ( (x > 128 && x <= 255) && y == 128 )
  {
    //    Serial.println("right ");
    pwm = pwm_calc( x);
    right ( pwm );
  }
  if ((x >= 0 && x < 128) && y == 128 )
  {
    Serial.println("left ");
    pwm = pwm_calc(x);
    left( pwm );
  }

  if (p_stick.Button(PSB_R2))
  {
    anti_clock_wise(40);
  }

  if (p_stick.Button(PSB_L2))
  {
    clock_wise(40);
  }

  //delay(1);

}

/*
  int* stick_values( )
  {
  static int stick [2];
  stick[0] = (p_stick.Analog(PSS_RX)) - 128;
  stick[1] = (p_stick.Analog(PSS_RY)) - 128;
  return stick;
  }
*/

int diff_pwm(int pwm) {
  int pwm2 = pwm * 0.866;
  return pwm2;
}


void forward(int pwm) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, pwm * 0.5);
  analogWrite(m2pwm, pwm * 1.54);
  analogWrite(m3pwm, pwm * 0.5);
}

void backward(int pwm) {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, pwm * 0.866);
  analogWrite(m2pwm, pwm);
  analogWrite(m3pwm, pwm * 0.866);
}

void left(int pwm) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm * 0.866);
  analogWrite(m3pwm, pwm * 0.866);
}

void right(int pwm) {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm * 0.866);
  analogWrite(m3pwm, pwm * 0.866);
}

void clock_wise(int pwm) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm);
  analogWrite(m3pwm, pwm);
}
void anti_clock_wise(int pwm) {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm);
  analogWrite(m3pwm, pwm);
}

void hard_brake(int intensity) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, intensity);
  analogWrite(m2pwm, intensity);
  analogWrite(m3pwm, intensity);
}

void soft_brake() {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, 35);
  analogWrite(m2pwm, 35);
  analogWrite(m3pwm, 35);
}

int pwm_calc(int stick_y)
{
  int temp_pwm;
  if ( stick_y > 128 && stick_y <= 0)
  {
    temp_pwm = (stick_y - 128);

    return ((temp_pwm * 2) - 1);
  }
  else
  {
    temp_pwm = (stick_y - 128);
    return (temp_pwm * 2 - 1);
  }
}
