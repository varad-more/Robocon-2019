int m1pwm = 5;
int m2pwm = 13;
int m3pwm = 10;
int m1p1 = 6;
int m1p2 = 7;
int m2p1 = 12;
int m2p2 = 11;
int m3p1 = 8;
int m3p2 = 9;

void forward(int );
void backward(int );
void left (int );
void right(int );
void clock_wise(int);
void anti_clock_wise(int );
void hard_brake ( int );
void soft_brake();

void setup() {
  pinMode(m1p1, OUTPUT);
  pinMode(m1p2, OUTPUT);
  pinMode(m2p1, OUTPUT);
  pinMode(m2p2, OUTPUT);
  pinMode(m3p1, OUTPUT);
  pinMode(m3p2, OUTPUT);
}

void loop() {

}


void forward(int pwm) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, pwm * 0.5);
  analogWrite(m2pwm, pwm * 1.54);
  analogWrite(m3pwm, pwm * 0.5);
}

void backward(int pwm) {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, pwm * 0.866);
  analogWrite(m2pwm, pwm);
  analogWrite(m3pwm, pwm * 0.866);
}

void left(int pwm) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm * 0.866);
  analogWrite(m3pwm, pwm * 0.866);
}

void right(int pwm) {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm * 0.866);
  analogWrite(m3pwm, pwm * 0.866);
}

void clock_wise(int pwm) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm);
  analogWrite(m3pwm, pwm);
}
void anti_clock_wise(int pwm) {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm);
  analogWrite(m3pwm, pwm);
}

void hard_brake(int intensity) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, intensity);
  analogWrite(m2pwm, intensity);
  analogWrite(m3pwm, intensity);
}

void soft_brake() {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, 35);
  analogWrite(m2pwm, 35);
  analogWrite(m3pwm, 35);
}
