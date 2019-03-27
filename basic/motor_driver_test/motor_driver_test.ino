#define dir 50
#define pwm 9
#define brk 51


//#define brk2 28
//#define brk3 29

void setup() {
  // put your setup code here, to run once:
pinMode(dir,OUTPUT);
pinMode(brk,OUTPUT);
pinMode(pwm,OUTPUT);
digitalWrite(brk,LOW);
}

//dir - low - actuator comes out and vice versa

void loop() {
digitalWrite(pwm,HIGH);
//analogWrite(pwm1,HIGH);
digitalWrite(dir,HIGH);

}

//int brake[2][2]={{26,27},{28,29}};//checked 
