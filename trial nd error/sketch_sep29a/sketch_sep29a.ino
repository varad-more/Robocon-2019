#include <SPI.h> // Included for SFE_LSM9DS0 library
#include <Wire.h>
#include <SFE_LSM9DS0.h>
#include <XBOXRECV.h>
#include <math.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#define maxSpeed 255

USB Usb;
XBOXRECV Xbox(&Usb);
int xboxNumber = 0;


#define LSM9DS0_XM  0x1D // Would be 0x1E if SDO_XM is LOW
#define LSM9DS0_G   0x6B // Would be 0x6A if SDO_G is LOW

LSM9DS0 dof(MODE_I2C, LSM9DS0_G, LSM9DS0_XM);

#define PRINT_CALCULATED

#define PRINT_SPEED 500 // 500 ms between prints

#define Kp 2.5  // 
#define Ki 2.5  // 
#define MaxSpeed 240
#define baseSpeed 100
//int lsm_in = A14;
//int lsm_in1 = A15;


struct vector {
  double Direction;
  int Magnitude;
};
struct vector Vector;

double vector_direction(uint8_t);
double Heading(float , float);
//int setpoint = controller input;
int error = 0;
int sensorVal = 0;
int lastError = 0;
void pid (float);
void setup()
{
  Serial.begin(115200); // Start serial at 115200 bps
  // Use the begin() function to initialize the LSM9DS0 library.
  // You can either call it with no parameters (the easy way):
  uint16_t status = dof.begin();
  // Or call it with declarations for sensor scales and data rates:
  //uint16_t status = dof.begin(dof.G_SCALE_2000DPS,
  //                            dof.A_SCALE_6G, dof.M_SCALE_2GS);

  // begin() returns a 16-bit value which includes both the gyro
  // and accelerometers WHO_AM_I response. You can check this to
  // make sure communication was successful.
  Serial.print("LSM9DS0 WHO_AM_I's returned: 0x");
  Serial.println(status, HEX);
  Serial.println("Should be 0x49D4");
  Serial.println();

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));

}

void loop()
{ float heading ;
  do {
    Usb.Task();
    if (Xbox.XboxReceiverConnected) {
      for (uint8_t i = 0; i < 4; i++) {
        if (Xbox.Xbox360Connected[i]) {
          xboxNumber = i;
          else if (!Xbox.getButtonPress(L1, i) && !Xbox.getButtonPress(R1, i)) {
            //            GET VECTOR DIRECTION
            Vector.Direction = vector_direction(i);
            heading = Heading(dof.mx,dof.my);
           error=Vector.Direction-heading;
           pid(error);          
           }




          void pid(float error)
          { // pin not yet declared
            float heading = analogRead(_____);
            // If no line is detected, stay at the position

            // error = heading - setPoint;   // Calculate the deviation from position to the set point
             motorSpeed = Kp * error + Kd * (error - lastError)+ (motor_speed) ;   // Applying formula of PID
            lastError = error;    // Store current error as previous error for next iteration use
           

            

          }

          double Heading(float hx, float hy)
          {
            float heading;

            if (hy > 0)
            {
              heading = 90 - (atan(hx / hy) * (180 / PI));
            }
            else if (hy < 0)
            {
              heading = - (atan(hx / hy) * (180 / PI));
            }
            else // hy = 0
            {
              if (hx < 0) heading = 180;
              else heading = 0;
            }
            //  Serial.print("hx\t");
            //  Serial.print(hx);
            //  Serial.print("\thy\t");
            //  Serial.print(hy);
            if (hx > 0 && hy < 0)
            {
              heading = map(heading, 90, 0, 0, 90);
            }
            else if (hx < 0 && hy < 0)
            {
              heading = map(heading, 0, -90, 90, 180);
            }
            else if (hx < 0 && hy > 0)
            {
              heading = map(heading, 180, 90, 180, 270);
            }
            else if (hx > 0 && hy > 0)
            {
              heading = map(heading, 90, 0, 270, 360);
            }
            Serial.print("\tHeading: ");
            Serial.println(heading);
          return heading ;
          }
