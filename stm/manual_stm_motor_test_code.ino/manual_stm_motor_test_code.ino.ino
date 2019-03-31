struct motor {
  int dir_r;
  int dir_l;
  int pwm;
};

struct motor MA, MB, MC;


void setup() {
  // put your setup code here, to run once:
  //  GPIOA = 0xffff;
  //  afio_cfg_debug_ports(AFIO_DEBUG_NONE);
  Serial.begin(9600);
  Serial.println("aa");
  MA.pwm = PA8;  //PA8;
  MB.pwm = PB0;
  MC.pwm = PB1;
  MA.dir_r = PB12;
  MA.dir_l = PB13;
  MB.dir_r = PB14;
  MB.dir_l = PB15;
  MC.dir_r = PA15;
  MC.dir_l = PB3;

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
  Serial.println("workinh");
  go();
  delay(1000);
  sto_p();
  delay(1000);
}

void go ()
{

  digitalWrite(MA.dir_r, HIGH);
  digitalWrite(MA.dir_l, LOW);
  digitalWrite(MB.dir_r, HIGH);
  digitalWrite(MB.dir_l, LOW);
  digitalWrite(MC.dir_r, HIGH);
  digitalWrite(MC.dir_l, LOW);
  analogWrite(MA.pwm, 120);
  analogWrite(MB.pwm, 120);
  analogWrite(MC.pwm, 120);
}

void sto_p()
{

  digitalWrite(MA.dir_r, LOW);
  digitalWrite(MA.dir_l, LOW);
  digitalWrite(MB.dir_r, LOW);
  digitalWrite(MB.dir_l, LOW);
  digitalWrite(MC.dir_r, LOW);
  digitalWrite(MC.dir_l, LOW);
  analogWrite(MA.pwm, 0);
  analogWrite(MB.pwm, 0);
  analogWrite(MC.pwm, 0);
}
