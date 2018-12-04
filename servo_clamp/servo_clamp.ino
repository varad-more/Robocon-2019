int servo_1=5;
//int servo_2=10;
int pulse=1500;
void setup() {
  // put your setup code here, to run once:
pinMode(servo_1,OUTPUT);
//pinMode(servo_2,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(servo_1, HIGH);
//digitalWrite(servo_2, HIGH);
delayMicroseconds(500);
digitalWrite(servo_1,LOW);
//digitalWrite(servo_2,LOW);
delay(20);
digitalWrite(servo_1, HIGH);
//digitalWrite(servo_2, HIGH);
delayMicroseconds(1500);
digitalWrite(servo_1,LOW);
//digitalWrite(servo_2,LOW);
delay(20);
}
