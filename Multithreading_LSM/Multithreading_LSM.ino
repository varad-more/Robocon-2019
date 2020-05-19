#include <Scheduler.h>
//B6--SCL  B7--SDA

#include <SPI.h> // Included for SFE_LSM9DS0 library
#include <Wire.h>
#include <SFE_LSM9DS0.h>

#define LSM9DS0_XM  0x1D // Would be 0x1E if SDO_XM is LOW
#define LSM9DS0_G   0x6B// Would be 0x6A if SDO_G is LOW

LSM9DS0 dof(MODE_I2C, LSM9DS0_G, LSM9DS0_XM);

#define GyroMeasError PI * (40.0f / 180.0f)       // gyroscope measurement error in rads/s (shown as 3 deg/s)
#define GyroMeasDrift PI * (0.0f / 180.0f)      // gyroscope measur ement drift in rad/s/s (shown as 0.0 deg/s/s)
#define beta sqrt(3.0f / 4.0f) * GyroMeasError   // compute beta
#define zeta sqrt(3.0f / 4.0f) * GyroMeasDrift   // compute zeta, the other free parameter in the Madgwick scheme usually set to a small or zero value
#define Kp 2.0f * 5.0f // these are the free parameters in the Mahony filter and fusion scheme, Kp for proportional feedback, Ki for integral
#define Ki 0.0f


float pitch, yaw, roll, heading;
float deltat = 0.0f;        // integration interval for both filter schemes
uint32_t lastUpdate = 0;    // used to calculate integration interval
uint32_t Now = 0;           // used to calculate integration interval

float abias[3] = {0, 0, 0}, gbias[3] = {0, 0, 0};
float ax, ay, az, gx, gy, gz, mx, my, mz; // variables to hold latest sensor data values
float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};    // vector to hold quaternion
float eInt[3] = {0.0f, 0.0f, 0.0f};       // vector to hold integral error for Mahony method
int i=1;
float refrenceheading_;


int led1 = PB8;
int led2 = PB9;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Start serial at 38400 bps
  uint32_t status = dof.begin();

  Serial.print("LSM9DS0 WHO_AM_I's returned: 0x");
  Serial.println(status, HEX);
  Serial.println("Should be 0x49D4");
  Serial.println();

  dof.setAccelScale(dof.A_SCALE_2G);
  dof.setGyroScale(dof.G_SCALE_245DPS);
  dof.setMagScale(dof.M_SCALE_2GS);
  dof.setAccelODR(dof.A_ODR_200); // Set accelerometer update rate at 100 Hz
  dof.setAccelABW(dof.A_ABW_50); // Choose lowest filter setting for low noise
  dof.setGyroODR(dof.G_ODR_190_BW_125);  // Set gyro update rate to 190 Hz with the smallest bandwidth for low noise
  dof.setMagODR(dof.M_ODR_125); // Set magnetometer to update every 80 ms
  dof.calLSM9DS0(gbias, abias);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  Scheduler.startLoop(loop2);
  Scheduler.startLoop(lsm);
 // Scheduler.startLoop(loop4);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(led1, HIGH);

  // IMPORTANT:
  // When multiple tasks are running 'delay' passes control to
  // other tasks while waiting and guarantees they get executed.
  delay(1000);
  digitalWrite(led1, LOW);
  delay(1000);

}

void loop2() {
  digitalWrite(led2, HIGH);
  delay(100);
  digitalWrite(led2, LOW);
  delay(100);
}

void lsm(){
  dof.readGyro();           // Read raw gyro data
  gx = dof.calcGyro(dof.gx) - gbias[0];   // Convert to degrees per seconds, remove gyro biases
  gy = dof.calcGyro(dof.gy) - gbias[1];
  gz = dof.calcGyro(dof.gz) - gbias[2];

  dof.readAccel();         // Read raw accelerometer data
  ax = dof.calcAccel(dof.ax) - abias[0];   // Convert to g's, remove accelerometer biases
  ay = dof.calcAccel(dof.ay) - abias[1];
  az = dof.calcAccel(dof.az) - abias[2];

  dof.readMag();           // Read raw magnetometer data
  mx = dof.calcMag(dof.mx);     // Convert to Gauss and correct for calibration
  my = dof.calcMag(dof.my);
  mz = dof.calcMag(dof.mz);

  Now = micros();
  deltat = ((Now - lastUpdate) / 1000000.0f); // set integration time by time elapsed since last filter update
  lastUpdate = Now;
  MadgwickQuaternionUpdate(ax, ay, az, gx * PI / 180.0f, gy * PI / 180.0f, gz * PI / 180.0f, mx, my, mz);
 if(i==1)   
 {delay(1000);
    refrenceheading_=refrenceheading(mx,my);
    Serial.println("refrance taken as");
     Serial.println(refrenceheading_);
    i++;
 }

  printHeading(mx, my,refrenceheading_);
}


void printHeading(float hx, float hy,float refrenceheading_)
{
  float new_heading ;
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
    if (hy > 0 && hx > 0)
  {
    float new_heading = map(heading , 90, 0, 0, 90);
    Serial.print("Heading: ");
    Serial.println(new_heading , 2);
  }
     else if (hy > 0 && hx < 0 )
    {
       float new_heading = map(heading , -90, 0, 90, 180);
       Serial.print("Heading: ");
       Serial.println(new_heading , 2);
    }
   else if  (hx < 0 && hy < 0)
    {
      float new_heading = map(heading , 90, 0, -90, -180);
      Serial.print("Heading: ");
      Serial.println(new_heading , 2);
    }
////    if (hx>0 && hy<0)
    else
//    if(hx>0 && hy <0) 
    {
   float new_heading = map(heading , 0, -90, 0, -90);
      Serial.print("Heading: ");
      Serial.println(new_heading , 2);
    }
new_heading-=refrenceheading_;
if(new_heading > 180) new_heading-=360;
if(new_heading < -180) new_heading+=360;
Serial.print(heading );
Serial.print("     hx ");
Serial.print(hx);
Serial.print(" hy");
Serial.print(hy);
Serial.print("   required values ");
Serial.print(new_heading);
Serial.println("   ");  

}

void printOrientation(float x, float y, float z)
{

  pitch = atan2(x, sqrt(y * y) + (z * z));
  roll = atan2(y, sqrt(x * x) + (z * z));
  pitch *= 180.0 / PI;
  roll *= 180.0 / PI;

}

void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz)
{
  float q1 = q[0], q2 = q[1], q3 = q[2], q4 = q[3];   // short name local variable for readability
  float norm;
  float hx, hy, _2bx, _2bz;
  float s1, s2, s3, s4;
  float qDot1, qDot2, qDot3, qDot4;

  // Auxiliary variables to avoid repeated arithmetic
  float _2q1mx;
  float _2q1my;
  float _2q1mz;
  float _2q2mx;
  float _4bx;
  float _4bz;
  float _2q1 = 2.0f * q1;
  float _2q2 = 2.0f * q2;
  float _2q3 = 2.0f * q3;
  float _2q4 = 2.0f * q4;
  float _2q1q3 = 2.0f * q1 * q3;
  float _2q3q4 = 2.0f * q3 * q4;
  float q1q1 = q1 * q1;
  float q1q2 = q1 * q2;
  float q1q3 = q1 * q3;
  float q1q4 = q1 * q4;
  float q2q2 = q2 * q2;
  float q2q3 = q2 * q3;
  float q2q4 = q2 * q4;
  float q3q3 = q3 * q3;
  float q3q4 = q3 * q4;
  float q4q4 = q4 * q4;

  // Normalise accelerometer measurement
  norm = sqrt(ax * ax + ay * ay + az * az);
  if (norm == 0.0f) return; // handle NaN
  norm = 1.0f / norm;
  ax *= norm;
  ay *= norm;
  az *= norm;

  // Normalise magnetometer measurement
  norm = sqrt(mx * mx + my * my + mz * mz);
  if (norm == 0.0f) return; // handle NaN
  norm = 1.0f / norm;
  mx *= norm;
  my *= norm;
  mz *= norm;

  // Reference direction of Earth's magnetic field
  _2q1mx = 2.0f * q1 * mx;
  _2q1my = 2.0f * q1 * my;
  _2q1mz = 2.0f * q1 * mz;
  _2q2mx = 2.0f * q2 * mx;
  hx = mx * q1q1 - _2q1my * q4 + _2q1mz * q3 + mx * q2q2 + _2q2 * my * q3 + _2q2 * mz * q4 - mx * q3q3 - mx * q4q4;
  hy = _2q1mx * q4 + my * q1q1 - _2q1mz * q2 + _2q2mx * q3 - my * q2q2 + my * q3q3 + _2q3 * mz * q4 - my * q4q4;
  _2bx = sqrt(hx * hx + hy * hy);
  _2bz = -_2q1mx * q3 + _2q1my * q2 + mz * q1q1 + _2q2mx * q4 - mz * q2q2 + _2q3 * my * q4 - mz * q3q3 + mz * q4q4;
  _4bx = 2.0f * _2bx;
  _4bz = 2.0f * _2bz;

  // Gradient decent algorithm corrective step
  s1 = -_2q3 * (2.0f * q2q4 - _2q1q3 - ax) + _2q2 * (2.0f * q1q2 + _2q3q4 - ay) - _2bz * q3 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q4 + _2bz * q2) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q3 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
  s2 = _2q4 * (2.0f * q2q4 - _2q1q3 - ax) + _2q1 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q2 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + _2bz * q4 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q3 + _2bz * q1) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q4 - _4bz * q2) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
  s3 = -_2q1 * (2.0f * q2q4 - _2q1q3 - ax) + _2q4 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q3 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + (-_4bx * q3 - _2bz * q1) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q2 + _2bz * q4) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q1 - _4bz * q3) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
  s4 = _2q2 * (2.0f * q2q4 - _2q1q3 - ax) + _2q3 * (2.0f * q1q2 + _2q3q4 - ay) + (-_4bx * q4 + _2bz * q2) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q1 + _2bz * q3) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q2 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
  norm = sqrt(s1 * s1 + s2 * s2 + s3 * s3 + s4 * s4);    // normalise step magnitude
  norm = 1.0f / norm;
  s1 *= norm;
  s2 *= norm;
  s3 *= norm;
  s4 *= norm;

  // Compute rate of change of quaternion
  qDot1 = 0.5f * (-q2 * gx - q3 * gy - q4 * gz) - beta * s1;
  qDot2 = 0.5f * (q1 * gx + q3 * gz - q4 * gy) - beta * s2;
  qDot3 = 0.5f * (q1 * gy - q2 * gz + q4 * gx) - beta * s3;
  qDot4 = 0.5f * (q1 * gz + q2 * gy - q3 * gx) - beta * s4;

  // Integrate to yield quaternion
  q1 += qDot1 * deltat;
  q2 += qDot2 * deltat;
  q3 += qDot3 * deltat;
  q4 += qDot4 * deltat;
  norm = sqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);    // normalise quaternion
  norm = 1.0f / norm;
  q[0] = q1 * norm;
  q[1] = q2 * norm;
  q[2] = q3 * norm;
  q[3] = q4 * norm;

}


void MahonyQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz)
{
  float q1 = q[0], q2 = q[1], q3 = q[2], q4 = q[3];   // short name local variable for readability
  float norm;
  float hx, hy, bx, bz;
  float vx, vy, vz, wx, wy, wz;
  float ex, ey, ez;
  float pa, pb, pc;

  // Auxiliary variables to avoid repeated arithmetic
  float q1q1 = q1 * q1;
  float q1q2 = q1 * q2;
  float q1q3 = q1 * q3;
  float q1q4 = q1 * q4;
  float q2q2 = q2 * q2;
  float q2q3 = q2 * q3;
  float q2q4 = q2 * q4;
  float q3q3 = q3 * q3;
  float q3q4 = q3 * q4;
  float q4q4 = q4 * q4;

  // Normalise accelerometer measurement
  norm = sqrt(ax * ax + ay * ay + az * az);
  if (norm == 0.0f) return; // handle NaN
  norm = 1.0f / norm;        // use reciprocal for division
  ax *= norm;
  ay *= norm;
  az *= norm;

  // Normalise magnetometer measurement
  norm = sqrt(mx * mx + my * my + mz * mz);
  if (norm == 0.0f) return; // handle NaN
  norm = 1.0f / norm;        // use reciprocal for division
  mx *= norm;
  my *= norm;
  mz *= norm;

  // Reference direction of Earth's magnetic field
  hx = 2.0f * mx * (0.5f - q3q3 - q4q4) + 2.0f * my * (q2q3 - q1q4) + 2.0f * mz * (q2q4 + q1q3);
  hy = 2.0f * mx * (q2q3 + q1q4) + 2.0f * my * (0.5f - q2q2 - q4q4) + 2.0f * mz * (q3q4 - q1q2);
  bx = sqrt((hx * hx) + (hy * hy));
  bz = 2.0f * mx * (q2q4 - q1q3) + 2.0f * my * (q3q4 + q1q2) + 2.0f * mz * (0.5f - q2q2 - q3q3);

  // Estimated direction of gravity and magnetic field
  vx = 2.0f * (q2q4 - q1q3);
  vy = 2.0f * (q1q2 + q3q4);
  vz = q1q1 - q2q2 - q3q3 + q4q4;
  wx = 2.0f * bx * (0.5f - q3q3 - q4q4) + 2.0f * bz * (q2q4 - q1q3);
  wy = 2.0f * bx * (q2q3 - q1q4) + 2.0f * bz * (q1q2 + q3q4);
  wz = 2.0f * bx * (q1q3 + q2q4) + 2.0f * bz * (0.5f - q2q2 - q3q3);

  // Error is cross product between estimated direction and measured direction of gravity
  ex = (ay * vz - az * vy) + (my * wz - mz * wy);
  ey = (az * vx - ax * vz) + (mz * wx - mx * wz);
  ez = (ax * vy - ay * vx) + (mx * wy - my * wx);
  if (Ki > 0.0f)
  {
    eInt[0] += ex;      // accumulate integral error
    eInt[1] += ey;
    eInt[2] += ez;
  }
  else
  {
    eInt[0] = 0.0f;     // prevent integral wind up
    eInt[1] = 0.0f;
    eInt[2] = 0.0f;
  }

  // Apply feedback terms
  gx = gx + Kp * ex + Ki * eInt[0];
  gy = gy + Kp * ey + Ki * eInt[1];
  gz = gz + Kp * ez + Ki * eInt[2];

  // Integrate rate of change of quaternion
  pa = q2;
  pb = q3;
  pc = q4;
  q1 = q1 + (-q2 * gx - q3 * gy - q4 * gz) * (0.5f * deltat);
  q2 = pa + (q1 * gx + pb * gz - pc * gy) * (0.5f * deltat);
  q3 = pb + (q1 * gy - pa * gz + pc * gx) * (0.5f * deltat);
  q4 = pc + (q1 * gz + pa * gy - pb * gx) * (0.5f * deltat);

  // Normalise quaternion
  norm = sqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);
  norm = 1.0f / norm;
  q[0] = q1 * norm;
  q[1] = q2 * norm;
  q[2] = q3 * norm;
  q[3] = q4 * norm;

}
float refrenceheading(float hx,float hy)
{
  float new_heading ;
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
    
if (hy > 0 && hx > 0)
  {
    float new_heading = map(heading , 90, 0, 0, 90);
    Serial.print("Heading: ");
    Serial.println(new_heading , 2);
  }
     else if (hy > 0 && hx < 0 )
    {
       float new_heading = map(heading , -90, 0, 90, 180);
       Serial.print("Heading: ");
       Serial.println(new_heading , 2);
    }
   else if  (hx < 0 && hy < 0)
    {
      float new_heading = map(heading , 90, 0, -90, -180);
      Serial.print("Heading: ");
      Serial.println(new_heading , 2);
    }
////    if (hx>0 && hy<0)
    else
//    if(hx>0 && hy <0) 
    {
   float new_heading = map(heading , 0, -90, 0, -90);
      Serial.print("Heading: ");
      Serial.println(new_heading , 2);
    }
return new_heading;
}


