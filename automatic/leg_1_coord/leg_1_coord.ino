//  pins
const int a_1 = 4;
const int a_2 = 5;//assign relay INx pin to arduino pin
const int b_1 = 7;
const int b_2 = 6;
const int pot_1 = A0;
const int pot_2 = A1;


//variables
float  x, y ;

float T1;
float T2;

//
long int flag1 = 1;
long int flag2 = 1;
long int t1, t2;
//constants

float pi = 3.14159;
float r1 = 0;
float phi1 = 0;
float phi2 = 0;
float phi3 = 0;
float a1 = 0;
float a2 = 39;
float a3 = 0;
float a4 = 39;




//functions
void movement (float , float);
void cont_1 ();
void exp_1 ();
void cont_2 ();
void exp_2 ();
void stop_1();
void stop_2();
void gotopos(float , float);
void calculate_neg_angle(float, float);
void calculate_pos_angle(float, float);

void setup() {

  Serial.begin(9600);
  pinMode(a_1, OUTPUT);//set relay as an output
  pinMode(a_2, OUTPUT);//set relay as an output
  pinMode(b_1, OUTPUT);//set relay as an output
  pinMode(b_2, OUTPUT);//set relay as an output


}

void loop() {

//  while (flag1 != 1 && flag2 != 1)
//  {
//    gotopos(40, 50);
//  }
//  flag1=1;flag2=1;
//  while (flag1 != 0 && flag2 != 0)
//  {
    gotopos(10, 40);
//  }


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

//pot1
//0-950
//110-830
//pot2
//15-280
//170-920
void movement(float T1 , float  T2)
{
  float ang1, ang2;
  int p1, p2;
  //  ang1 = T1;
  //  ang2 = T2;
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
  else if (n >= 465 && n < 784)
    p2 = map (n , 465 , 784, 45, 90 );
  else if (n >= 784 && n < 892)
    p2 = map (n, 784, 892, 90, 135);
  else if (n >= 892 && n < 916)
    p2 = map (n , 892, 916, 135, 160);
  else
    p2 = map (n, 278, 916, 10, 160);



  //int flag1=1,flag2=1;


  if (p1 > T1 + 1.5)
  {
    exp_1();
  }
  else if (p1 < T1 - 1.5)
  {
    cont_1();
  }
  else if (p1 <= T1 + 1.5 || p1 >= T1 - 1.5)
  {
    stop_1();
    flag1=0;
    
  }


  if (p2 < T2 - 1.5)
  {
    exp_2();
  }
  else if (p2 > T2 + 1.5)
  {
    cont_2();
  }
  else  if (p2 <= T2 + 1.5 || p2 >= T2 - 1.5)
  {
    stop_2();
    flag2=0;
    
  }


  Serial.print(m); Serial.print(" "); Serial.print(n); Serial.print(" "); Serial.print(p1); Serial.print(" "); Serial.print(T1); Serial.print(" "); Serial.print(p2); Serial.print(" "); Serial.println(T2);

}

void gotopos(float x , float y )
{
  //  float x0=0,y0=55.15,

  if (x < 0)
  {
    calculate_neg_angle(x, y);
  }
  else
  {
    calculate_pos_angle(x, y);
  }
}


void calculate_pos_angle(float x1, float y1)
{

  r1 = sqrt(x1 * x1 + y1 * y1);
  //    Serial.print("  r1  ");
  //    Serial.print(r1);
  phi1 = acos (((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
  //    Serial.print(" ");
  //    Serial.print("  phi1  ");
  //    Serial.print(phi1);
  phi2 = atan(y1 / x1);
  //  Serial.print(" ");
  //    Serial.print("  phi2  ");
  //    Serial.print(phi2);
  T1 = phi2 - phi1;

  phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
  //  Serial.print(" ");
  //    Serial.print("  phi3  ");
  //    Serial.print(phi3);
  T2 = pi - phi3;

  T1 = T1 * 180 / pi;
  T2 = T2 * 180 / pi;
  movement ( T1,  T2);
  //  Serial.print(" ");
  //    Serial.print("  T1  ");
  //    Serial.print(T1);
  //    Serial.print(" ");
  //    Serial.print("  T2  ");
  //    Serial.println(T2);

  //  T2 = T2 - 360;
}

void calculate_neg_angle(float x1 , float y1)
{
  x1 = abs(x1);
  r1 = sqrt(x1 * x1 + y1 * y1);
  //  Serial.print("  r1  ");
  //  Serial.println(r1);
  phi1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
  //  Serial.print("  phi1  ");
  //  Serial.println(phi1);
  phi2 = atan(-y1 / x1);
  phi2 = pi + phi2;
  //  Serial.print("  phi2  ");
  //  Serial.println(phi2);
  T1 = phi2 - phi1;
  phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
  //  Serial.print("  phi3  ");
  //  Serial.println(phi3);
  T2 = pi - phi3;

  T1 = T1 * 180 / pi;
  T2 = T2 * 180 / pi;
  movement ( T1,  T2);
  //  Serial.print("  T1  ");
  //  Serial.println(T1);
  //  Serial.print("  T2  ");
  //  Serial.println(T2);
  //  T2 = T2 - 360;
}
