const int a_1 = 4;
const int a_2 = 5;//assign relay INx pin to arduino pin
const int b_1 = 7;
const int b_2 = 6;
const int pot_1 = A0;
const int pot_2 = A1;

void cont_1 ();
void exp_1 ();
void cont_2 ();
void exp_2 ();
void stop_1();
void stop_2();



void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(a_1, OUTPUT);//set relay as an output
  pinMode(a_2, OUTPUT);//set relay as an output
  pinMode(b_1, OUTPUT);//set relay as an output
  pinMode(b_2, OUTPUT);//set relay as an output
}

void loop() {
  // put your main code here, to run repeatedly:
int p1, p2;
//  ang1=
  int m = analogRead(pot_1);
  int n = analogRead(pot_2);

  if (m <= 953 && m > 917)
    p1 = map ( m , 955, 912, 8, 45);
  else if (m <= 917 && m > 873)
    p1 = map(m, 912, 873, 45, 90);
  else if (m <= 873 && m >= 831)
    p1 = map(m, 873, 825, 90, 100);
  else
    p1 = map (m, 953, 825, 10, 100); //70, 170, 753, 179);

  //  p1 = map (ang1, 110, 15, 830, 946); //70, 170, 753, 179);
  if (n >= 278 && n < 465)
    p2 = map (n , 278 , 465 , 10, 45);
  else if (n >= 465 && n < 863)
    p2 = map (n , 465 , 784, 45, 90 );
  else if (n >= 784 && n < 892)
    p2 = map (n, 784, 892, 90, 135);
  else if (n >= 892 && n < 916)
    p2 = map (n , 892, 916, 135, 160);
  else
    p2 = map (n, 278, 916, 10, 160); //-160, 15, 110, 858);
Serial.print(m); Serial.print(" "); Serial.print(n); Serial.print(" ");Serial.print(p1); Serial.print(" ");/* Serial.print(T1); Serial.print(" ")*/; Serial.println(p2);/* Serial.print(" "); Serial.println(T2);*/
cont_1();
//cont_2();
}


void cont_1 ()
{
  digitalWrite(a_1, LOW);
  digitalWrite(a_2, HIGH);
}
void exp_1 ()
{
  digitalWrite(a_2, LOW);
  digitalWrite(a_1, HIGH);
}
void cont_2 ()
{
  digitalWrite(b_1, LOW);
  digitalWrite(b_2, HIGH);
}
void exp_2 ()
{
  digitalWrite(b_2, LOW);
  digitalWrite(b_1, HIGH);
}

void stop_1 ()
{
  digitalWrite(a_2, LOW);
  digitalWrite(a_1, LOW);
}
void stop_2 ()
{
  digitalWrite(b_2, LOW);
  digitalWrite(b_1, LOW);
}
