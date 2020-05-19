/*
  I2C Pinouts
  SDA -> A4
  SCL -> A5
*/
#include <Wire.h>
#define SLAVE_ADDRESS 0x04
volatile int n=0;
volatile char t;
int c=0;
void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  //  Wire.onRequest(sendData);
}
  
void loop() {
 
//print (n)
} // end loop

// callback for received data
void receiveData(int byteCount) {
  
 while(Wire.available())
     {
      
   t =(Wire.read()); // Read next character
    //Serial.println(t);
     
//Serial.println(n); 
if (t == '-')
{
c =1;
  }

//else if (t == 46)
//{
//  Serial.println ("END");
//  continue;
//  }
else if( t == ',')
{
  if (c==1)
  {  n=-n;
  c=0; 
  }
  Serial.println(n);
  n=0;
}

else{
  
 n *= 10;
     n += t-48;   
   //  Serial.println(n); 
     }
}
}
