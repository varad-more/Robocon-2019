#include<Servo.h>

//struct clamp_servo{
Servo s1,s2;
void setup() {
  // put your setup code here, to run once:
s1.attach(5);
s2.attach(3);
//s2.s.attach(10);
}
//int i=1;
void loop() {
  // put your main code here, to run repeatedly:

/*
s1.s.write(0);
s2.s.write(0);
delay(500);*/
s2.write(100);
delay(2000);
s1.write(90);
delay(2000);
s1.write(170);
delay(10000);
s1.write(90);
delay(2000);
s2.write(60);
delay(2000);



//*/
/*s1.s.write(180);
s2.s.write(180);
delay (500);


s1.s.write(-180);
s2.s.write(-180);
delay (500);
*/
}
