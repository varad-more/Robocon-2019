#include<Servo.h>

struct clamp_servo{
Servo s; 
  }
 s1,s2;
void setup() {
  // put your setup code here, to run once:
s1.s.attach(9);
s2.s.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:

/*
s1.s.write(0);
s2.s.write(0);
delay(500);*/


s1.s.write(0);
s2.s.write(0);
s1.s.write(90);
s2.s.write(90);
delay(15);


/*
s1.s.write(-90);
s2.s.write(-90);
delay (500);
*/
/*s1.s.write(180);
s2.s.write(180);
delay (500);


s1.s.write(-180);
s2.s.write(-180);
delay (500);
*/
}
