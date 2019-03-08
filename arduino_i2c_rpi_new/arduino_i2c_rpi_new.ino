/*
  I2C Pinouts
  SDA -> A4
  SCL -> A5
*/

//Import the library required
#include <Wire.h>

//Slave Address for the Communication
#define SLAVE_ADDRESS 0x04

int motorspeed[2];
int count = 0;

//Code Initialization
void setup() {
  // initialize i2c as slave
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  Wire.begin(SLAVE_ADDRESS);
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  //  Wire.onRequest(sendData);
}

void loop() {
  //delay(100);
  //Serial.println(" new");
  analogWrite(5,motorspeed[0]);
  analogWrite(6,motorspeed[1]);
} // end loop

// callback for received data
void receiveData(int byteCount) {
  while(Wire.available())
  {
 if(count>1) 
   {count=0;
   }
motorspeed[count]=Wire.read();
Serial.println(count);
if(count==0) 
{
  Serial.print("rightspeed=");
}
else
{ Serial.print("leftspeed=");
}
Serial.println(motorspeed[count]);
count++;
}
}
