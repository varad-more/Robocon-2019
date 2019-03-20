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
  Serial.begin(9600);
  for (int i = 24 ; i < 32 ; i++)
  {
    pinMode(i, OUTPUT);
  }
  for (int j = 2; j < 6; j++)
  {
    pinMode(j, OUTPUT);
    analogWrite(j,255);
  }
}

bool flag1 = 0, flag2 = 0;
char dir = 's';
byte data[5] = {};

void loop() {
  // put your main code here, to run repeatedly:

   while(Serial.available() > 0)
  {
    data[0] = Serial.read();
    Serial.print(data[0]);
    if(data[0] == 's')
    {
      brakes();
    }
    else if(data[0] == 'f')
    {
      Serial.print(data[1]);
      forward(atoi(data[1]),atoi(data[2]));
    }
    else if(data[0] == 'b')
    {
      backward(atoi(data[1]),atoi(data[2]));
    }
  }
//backward(30,31);
//forward(26,27);
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

void brakes ()
{
  digitalWrite(24, HIGH);
  digitalWrite(25, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, HIGH);
  digitalWrite(28, HIGH);
  digitalWrite(29, HIGH);
  digitalWrite(30, HIGH);
  digitalWrite(31, HIGH);
}
