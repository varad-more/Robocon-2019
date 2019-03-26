#define dir 8
#define pwm 10
#define brk 12


#define dir1 9
#define pwm1 11
#define brk1 13

//#define brk2 28
//#define brk3 29

void setup() {
  // put your setup code here, to run once:
pinMode(dir,OUTPUT);
pinMode(dir1,OUTPUT);
pinMode(brk,OUTPUT);
pinMode(brk1,OUTPUT);
pinMode(pwm1,OUTPUT);
//pinMode(brk3,OUTPUT);
pinMode(pwm,OUTPUT);
}

//dir - low - actuator comes out and vice versa

void loop() {
  // put your main code here, to run repeatedly:
//digitalWrite(dir,LOW);
//analogWrite(pwm,255);
////digitalWrite(pwm,HIGH);
////digitalWrite(brk,HIGH);
//delay(1000);
//digitalWrite(brk,HIGH);
//delay (500);
digitalWrite(brk,HIGH);
digitalWrite(brk1,HIGH);
analogWrite(pwm,HIGH);
analogWrite(pwm1,HIGH);

}

//int brake[2][2]={{26,27},{28,29}};//checked 
