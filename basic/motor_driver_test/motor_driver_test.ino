#define dir 51
#define pwm 9
#define brk 50
//
/*
int pwm[4][2] = {{13,12}, {11,10}, {9,8}, {7,6}};
int driver[4][2] = {{25,29}, {33,37}, {41,45}, {49,53}};//50 KA 51,48 KA 49
int mpu [4][2] = {{38,40}, {42,44}, {46,48}, {50,52}};//yet to go 
int brake[4][2] = {{23,27}, {31,35}, {39,43}, {47,51}};*/

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
