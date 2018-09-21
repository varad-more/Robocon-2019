#include <SPI.h>
#include <Wire.h>
#include <SFE_LSM9DS0.h>

#define LSM9DS0_XM  0x1E // Would be 0x1D if SDO_XM is HIGH
#define LSM9DS0_G   0x6A // Would be 0x6B if SDO_G is HIGH

LSM9DS0 dof(MODE_I2C, LSM9DS0_G, LSM9DS0_XM);

unsigned long xlast_time_sampled = 0;
unsigned long xlast_time_printed = 0;
unsigned long ylast_time_sampled = 0;
unsigned long ylast_time_printed = 0;
float integral_x = 0, integral_y = 0;
float _xbias = 0.0, _ybias = 0.0;





void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  uint16_t status = dof.begin();
  Serial.print("LSM9DS0 WHO_AM_I's returned: 0x");
  Serial.println(status, HEX);
  Serial.println("Should be 0x49D4");
  Serial.println();

  delay(100);
  for (int i = 0; i < 200; i++)
  {
    dof.readGyro();
    dof.readAccel();
    _xbias += dof.calcAccel(dof.ax);
    _ybias += dof.calcAccel(dof.ay);
    delay(60);
  }
  _xbias = _xbias / 200;
  _ybias = _ybias / 200;
  Serial.println(_xbias);
  Serial.println(_ybias);
  delay(5000);



}

void loop() {
  dof.readGyro();
  dof.readAccel();
  dof.readMag();

  // put your main code here, to run repeatedly:
  float Ax = dof.calcAccel(dof.ax) - _xbias, Ay = dof.calcAccel(dof.ay) - _ybias;

  unsigned long x_now = micros(), y_now = micros();

  // Approximate the signal as a constant equal to the current sample
  // from the time of the previous sample until now.
  integral_x += Ax * (x_now - xlast_time_sampled) * pow(10, -6);
  xlast_time_sampled = x_now;
  Serial.print("Ax: ");
  Serial.print(Ax);
  Serial.print("  vx: ");
  //integral = map()
  Serial.print(integral_x);
  Serial.print(" ");

  // Approximate the signal as a constant equal to the current sample
  // from the time of the previous sample until now.
  integral_y += Ay * (y_now - ylast_time_sampled) * pow(10, -6);
  ylast_time_sampled = y_now;
  Serial.print("Ay: ");
  Serial.print(Ay);
  Serial.print("  vy: ");
  //integral = map()
  Serial.print(integral_y);
  Serial.print(" ");

  //float theeta = atan(integral_y/integral_x);
  float theeta = atan(integral_y / integral_x); //int(Ay*1000) / int(Ax*1000));
  Serial.print("  theeta:  ");
  Serial.print(theeta * 180 / PI);

  printHeading((float) dof.mx, (float) dof.my);
  delay(100);
}

void printHeading(float hx, float hy)
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
  Serial.print("hx\t");
  Serial.print(hx);
  Serial.print("\thy\t");
  Serial.print(hy);
  if (hx > 0 && hy < 0)
  {
    heading = map(heading, 90, 0, 90, 180);
  }
  else if (hx < 0 && hy < 0)
  {
    heading = map(heading, 0, -90, 180, 270);
  }
  else if (hx < 0 && hy > 0)
  {
    heading = map(heading, 180, 90, 270, 360);
  }
  else if (hx > 0 && hy > 0)
  {
    heading = map(heading, 90, 0, 0, 90);
  }
  Serial.print("\tHeading: ");
  Serial.println(heading);
}

