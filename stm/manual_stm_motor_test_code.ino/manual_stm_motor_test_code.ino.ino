struct motor {
  int dir_r;
  int dir_l;
  int pwm;
};

struct motor MA, MB, MC;


void setup() {
  // put your setup code here, to run once:
  MA.pwm = PA8;  //PA8;
  MB.pwm = PB1;
  MC.pwm = PB0;
  MA.dir_r = PB12;
  MA.dir_l = PB13;
  MB.dir_r = PB14;
  MB.dir_l = PB15;
  MC.dir_r = PA11;
  MC.dir_l = PA12;

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
  digitalWrite(MA.dir_r, HIGH);
  digitalWrite(MA.dir_l, LOW);
  digitalWrite(MB.dir_r, HIGH);
  digitalWrite(MB.dir_l, LOW);
  digitalWrite(MC.dir_r, HIGH);
  digitalWrite(MC.dir_l, LOW);
  analogWrite(MA.pwm, 255);
  analogWrite(MB.pwm, 255);
  analogWrite(MC.pwm, 255);
}
