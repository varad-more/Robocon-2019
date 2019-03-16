#define dir 34+1
#define brk 26+1
#define pwm 30+1


void setup() {
  // put your setup code here, to run once:
pinMode(dir,OUTPUT);
pinMode(brk,OUTPUT);
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
digitalWrite(brk,LOW);
digitalWrite(dir,HIGH);
analogWrite(pwm,255);
delay (1000);
}

//int brake[2][2]={{26,27},{28,29}};//checked 
