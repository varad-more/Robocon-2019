int pwmM1 = 13;
int pwmM2 = 10;
int pwmM3 = 5;
int M1D1 = 11;
int M1D2 = 12;
int M2D1 = 8;
int M2D2 = 9;
int M3D1 = 6;
int M3D2 = 7;
void forward(int pwm);
void backward(int pwm);
void left(int pwm);
void right(int pwm);

void setup() {

  pinMode(M1D1, OUTPUT);
  pinMode(M2D1, OUTPUT);
  pinMode(M3D1, OUTPUT);
  pinMode(M1D2, OUTPUT);
  pinMode(M2D2, OUTPUT);
  pinMode(M3D2, OUTPUT);
  pinMode(pwmM1, OUTPUT);
  pinMode(pwmM2, OUTPUT);
  pinMode(pwmM3, OUTPUT);

  digitalWrite(M1D1, HIGH);
  digitalWrite(M2D1, HIGH);
  digitalWrite(M3D1, HIGH);
  digitalWrite(M1D2, HIGH);
  digitalWrite(M2D2, HIGH);
  digitalWrite(M3D2, HIGH);

  analogWrite(pwmM1,5);
  analogWrite(pwmM2,5);
  analogWrite(pwmM3,5);
}

void loop() {
  digitalWrite(M1D1, LOW);
  digitalWrite(M2D1, HIGH);
  digitalWrite(M3D1, HIGH);
  digitalWrite(M1D2, HIGH);
  digitalWrite(M2D2, HIGH);
  digitalWrite(M3D2, HIGH);

  analogWrite(pwmM1,255);
  analogWrite(pwmM2,255);
  analogWrite(pwmM3,255);

}

void forward(int pwm){
  digitalWrite(M1D1, );
  digitalWrite(M2D1, );
  digitalWrite(M3D1, );
  digitalWrite(M1D2, );
  digitalWrite(M2D2, );
  digitalWrite(M3D2, );

  analogWrite(pwmM1,);
  analogWrite(pwmM2,);
  analogWrite(pwmM3,);

  }
void backward(int pwm)
{
  digitalWrite(M1D1, );
  digitalWrite(M2D1, );
  digitalWrite(M3D1, );
  digitalWrite(M1D2, );
  digitalWrite(M2D2, );
  digitalWrite(M3D2, );

  analogWrite(pwmM1,);
  analogWrite(pwmM2,);
  analogWrite(pwmM3,);

  
  }
void left (int pwm )
{
  digitalWrite(M1D1, );
  digitalWrite(M2D1, );
  digitalWrite(M3D1, );
  digitalWrite(M1D2, );
  digitalWrite(M2D2, );
  digitalWrite(M3D2, );

  analogWrite(pwmM1,);
  analogWrite(pwmM2,);
  analogWrite(pwmM3,);
  }

  void right (int pwm)
  {
  digitalWrite(M1D1, );
  digitalWrite(M2D1, );
  digitalWrite(M3D1, );
  digitalWrite(M1D2, );
  digitalWrite(M2D2, );
  digitalWrite(M3D2, );

  analogWrite(pwmM1,);
  analogWrite(pwmM2,);
  analogWrite(pwmM3,);

    }
