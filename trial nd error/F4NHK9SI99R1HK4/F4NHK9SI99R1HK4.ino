
//  NAME         : JIM BUI
//  NAME         : SERGEI DINES
//  NAME         : Dominic Cox
//  Affilation     : M.E.C.H. - University of South Florida
//  PURPOSE        : Motor + Servo Control Xbox 360 Controller
//  Revised        : 4 / 24 / 2015

#include <XBOXRECV.h>

USB Usb ;
XBOXRECV Xbox(&Usb) ;

int motorDir = 8 ; // Dir
int motorSpeed = 9; // PWM

int motorDir2 = 4; // Dir
int motorSpeed2 = 3; // PWM

int FWD1 = 1;
int BW1 = 0;
int FWD2 = 0;
int BW2 = 1;

void setup()
{
  Serial.begin(115200) ;
  Usb.Init() ;
  Serial.println( "Begin speed log." ) ;
  pinMode(motorDir , OUTPUT) ;
  pinMode(motorDir2, OUTPUT);
  pinMode(motorSpeed, OUTPUT);
  pinMode(motorSpeed2, OUTPUT);
}
void loop()
{
  Usb.Task() ;
  if (Xbox.XboxReceiverConnected)
  {
    int speed ;
    if (Xbox.getAnalogHat(LeftHatY , 0) > 1000)
    {
      speed = Xbox.getAnalogHat(LeftHatY , 0) / 131 ;
      digitalWrite(motorDir, 1);
      digitalWrite(motorDir2, 0);
      analogWrite(motorSpeed , speed) ;
      analogWrite(motorSpeed2, speed);
      Serial.print( "Motor speed: " ) ;
      Serial.print(Xbox.getAnalogHat(LeftHatY , 0) / 131) ;
      Serial.println() ;
    }
    else if (Xbox.getAnalogHat(LeftHatY, 0) < 1000)
    {
      speed = -Xbox.getAnalogHat(LeftHatY , 0) / 131 ;
      digitalWrite(motorDir, 0);
      digitalWrite(motorDir2, 1);
      analogWrite(motorSpeed , speed) ;
      analogWrite(motorSpeed2, speed);
      Serial.print( "Motor speed: " ) ;
      Serial.print(Xbox.getAnalogHat(LeftHatY , 0) / 131) ;
      Serial.println() ;
    }
    else
    {
      analogWrite(motorSpeed , 0) ;
      analogWrite(motorSpeed2, 0);
    }
    delay(1) ;
  }
  delay(1) ;
}
