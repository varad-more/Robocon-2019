// l1l1a = leg1link1(terminal)
#define l1l1a 24
#define l1l1b 25
#define l1l2a 26
#define l1l2b 27
#define l2l1a 28
#define l2l1b 29
#define l2l1a 30
#define l2l2a 31

void setup() {
  // put your setup code here, to run once:
  for (int i = 24 ; i < 32 ; i++)
  {
    pinMode(i, OUTPUT);
  }
  for (int j = 2; j < 6; j++)
  {
    pinMode(j, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(2, 150);
   analogWrite(3, 150);
    analogWrite(4, 150);
     analogWrite(5, 150);
 
//backward(24,/25);
forward(24,25);
 
}


void backward(int l1, int l2)
{
  digitalWrite(l2, HIGH);
  digitalWrite(l1, LOW);
}

void forward(int l1, int l2)
{
  digitalWrite(l2, LOW);
  digitalWrite(l1, HIGH);
}
