#include <PS2X_lib.h>
#include <AFMotor.h>
AF_DCMotor motor3(3);
AF_DCMotor motor2(2);
PS2X ps2x;
//const byte analogPin = 4;
const float Kp = 0.142;   // Kp value that you have to change
const float Kd = 4;   // Kd value that you have to change
const float Ki = 0;
float setHeading = 35;    // Middle point of sensor array
const int baseSpeed = 100;    // Base speed for your motors
const int maxSpeed = 200;   // Maximum speed for your motors
float currentHeading;
int error=0;
int motorSpeed,rightMotorSpeed,leftMotorSpeed;
 
byte type = 0;
byte vibrate = 0;
int dir ,accl;  // the directions & accelearation using console   
void setup() {
Serial.begin(57600);
error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
     }
  
}

void loop() {
  /*if (error == 1) //skip loop if no controller found
  {return; /*will make the builtin le of arduino blink in particular pattern */
  /*}*/
  
/*int positionVal =analogRead(analogPin); 
 // If no line is detected, stay at the position
 if(positionVal>950/*921)
 { */
    /*if(type == 1)
        {Serial.println("no controller found ");}*/
   /*else 
    */ if (type==1)
        {
        
       ps2x.read_gamepad(false, vibrate);
       if (ps2x.Button(PSB_R2))
       {int s3= -baseSpeed;
        int s2= baseSpeed;
        motor2.setSpeed(s2);
        motor3.setSpeed(s3);
        Serial.println(s2,s3);
          }
       if (ps2x.Button(PSB_L2))   
       {
        int s2= -baseSpeed;
        int s3= baseSpeed;
        motor2.setSpeed(s2);
        motor3.setSpeed(s3);
        Serial.println(s2,s3);
        }
       if( ps2x.Button(PSB_R1)) // print stick values if either is TRUE
       {
        //Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_RY), DEC); 
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC);
        dir= ps2x.Analog(PSS_RX);
        accl=ps2x.Analog(PSS_RY);
       if (dir ==128 && accl==128)
       {
        /*motor2.run(release);
       motor3.run(release);*/
      // Serial.println("no motion");
       }
       else if (dir==0 && accl==128)   // ANTICLOCKWISE ROTATTION, STICK TILTED TOWARDS LEFT  
       {
        int s2= -baseSpeed;
        int s3= baseSpeed;
        motor2.setSpeed(s2);
        motor3.setSpeed(s3);
        Serial.println(s2,s3);
        }  
       else if (dir==255 && accl==0)  // CLOCKWISE ROTATION , STICK TILTED RIGHT 
        {
        int s3= -baseSpeed;
        int s2= baseSpeed;
        motor2.setSpeed(s2);
        motor3.setSpeed(s3);
        Serial.println(s2,s3);
         }
         else if (dir==128 && accl==255 ) // FORWARD MOTION , STICK TILTED FORWARD 
       {
        int s3= baseSpeed;
        int s2= baseSpeed;
        motor2.setSpeed(s2);
        motor3.setSpeed(s3);
        Serial.println(s2,s3);
       }
       else if (dir==128 && accl==0 ) // REVERSE MOTION , STICK TILTED REVERSE
       {
        int s3= (-baseSpeed);
        int s2= (-baseSpeed);
        motor2.setSpeed(s2);
        motor3.setSpeed(s3); 
        Serial.println(s2,s3);
       }
       else if ((dir>=0&&dir<=128)&& (accl>=128&&accl<=255))  //  
       {
        int s2= (baseSpeed/2);
        int s3= (baseSpeed+maxSpeed);
        motor2.setSpeed(s2);
        motor3.setSpeed(s3);
        Serial.println(s2,s3);
      }
       else if ((dir>=0&&dir<=128) && (accl<=128&&accl>=0)) 
       {
        int s2= (-(baseSpeed/2));
        int s3= (-(baseSpeed+maxSpeed));
        motor2.setSpeed(s2);
        motor3.setSpeed(s3);
        Serial.println(s2,s3);
      }
       else if (dir<=255&&dir>=128 && accl>=0&&accl<=128) 
       {
        int s3= (-(baseSpeed/2));
        int s2= (-(baseSpeed+maxSpeed));
        motor2.setSpeed(s2);
        motor3.setSpeed(s3);
        Serial.println(s2,s3);
      } 
       else if ((dir<=255&&dir>=128) && (accl<=255&&accl>=128)) 
       {
        int s3= (baseSpeed/2);
        int s2= (baseSpeed+maxSpeed);
        motor2.setSpeed(s2);
        motor3.setSpeed(s3);
        Serial.println(s2,s3);
      } 
       
      } 
   
      
       
  /*console functions */
  
  }
/*else 
{
  //lsa control 
  
  }*/
delay(500);
  
}
