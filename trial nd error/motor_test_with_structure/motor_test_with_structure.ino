typedef struct motor {
  int dir_r;
  int dir_l;
  int pwm;
};
void clock_wise(int);
void anti_clock_wise(int);


struct motor MA, MB, MC;

void setup() {
  MA.pwm = 4;
  MB.pwm = 2;
  MC.pwm = 3;
  MA.dir_r = 32;
  MA.dir_l = 30;
  MB.dir_r = 24;
  MB.dir_l = 22;
  MC.dir_r = 28;
  MC.dir_l = 26;

  pinMode(MA.dir_r, OUTPUT);
  pinMode(MA.dir_l, OUTPUT);
  pinMode(MB.dir_r, OUTPUT);
  pinMode(MB.dir_l, OUTPUT);
  pinMode(MC.dir_r, OUTPUT);
  pinMode(MC.dir_l, OUTPUT);
  pinMode(MA.pwm, OUTPUT);
  pinMode(MB.pwm, OUTPUT);
  pinMode(MC.pwm, OUTPUT);
}

void loop() {
 //  put your main code here, to run repeatedly:
//  digitalWrite(MA.dir_r, HIGH);
//  digitalWrite(MA.dir_l, LOW);
  digitalWrite(MB.dir_r, LOW);
  digitalWrite(MB.dir_l, HIGH);
  digitalWrite(MC.dir_r, HIGH);
  digitalWrite(MC.dir_l, LOW);
//  analogWrite(MA.pwm, 40);
  analogWrite(MB.pwm, 40);
  analogWrite(MC.pwm, 40);
}  



void clock_wise(int pwm) {
  digitalWrite(MA.dir_r, HIGH);
  digitalWrite(MA.dir_l, LOW);
  digitalWrite(MB.dir_r, LOW);
  digitalWrite(MB.dir_l, HIGH);
  digitalWrite(MC.dir_r, HIGH);
  digitalWrite(MC.dir_l, LOW);
  analogWrite(MA.pwm, pwm);
  analogWrite(MB.pwm, pwm);
  analogWrite(MC.pwm, pwm);
}

void anti_clock_wise(int pwm) {
  digitalWrite(MA.dir_r, LOW);
  digitalWrite(MA.dir_l, HIGH);
  digitalWrite(MB.dir_r, HIGH);
  digitalWrite(MB.dir_l, LOW);
  digitalWrite(MC.dir_r, LOW);
  digitalWrite(MC.dir_l, HIGH);
  analogWrite(MA.pwm, pwm);
  analogWrite(MB.pwm, pwm);
  analogWrite(MC.pwm, pwm);
}