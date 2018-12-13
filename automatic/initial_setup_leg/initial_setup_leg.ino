// eqns
//


//  pins
const int a_1 = 4 ;
const int a_2 = 5;//assign relay INx pin to arduino pin
const int b_1 = 7;
const int b_2 = 6;
const int pot_1 = A0;
const int pot_2 = A1;


double max_1 = 30;
double max_2 = 38;
double min_1 =  20;
double min_2 = 23;

//constants
double pi = 3.14159;


// functions
void movement (int , int);
void cont_1 ();
void exp_1 ();
void cont_2 ();
void exp_2 ();
void initial_coord();
double* length_actuators (double , double);


// variables
double  theta_1;
double theta_2, alpha, beta, A_1, a = 39, k1, k2, gamma, cab;
double L_1, L_2, AB;
int p_1, p_2;

// trajectory variables
double y_o, x_o, x, y, x_1, y_1, OA, b = 39;
double a1 = 20, b1 = 10; //major and minor axis


void setup() {
  Serial.begin(9600);
  pinMode(a_1, OUTPUT);//set relay as an output
  pinMode(a_2, OUTPUT);//set relay as an output
  pinMode(b_1, OUTPUT);//set relay as an output
  pinMode(b_2, OUTPUT);//set relay as an output
  // initial point



}


void loop() {
  ////  leg_up();
  // /*
  // exp_1();
  // exp_2();*/
  //   cont_2();
//  cont_1();
  //int a = analogRead(A1);
  //Serial.print(a);
  //int b = analogRead(A0);
  //Serial.print(" ");
  //Serial.println(b);
  float ang1, ang2;
  int p1, p2;
  ang1 = 135;
  ang2 = -135;
  p1 = map (ang1, 70, 170, 753, 179);
  p2 = map (ang2, -160, 15, 110, 858);
  movement (p1, p2);
  //exp_1();
  //  int m = analogRead(pot_1);
  //  Serial.println(m);

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

double* length_actuators (double theta_1, double theta_2)
{
  static double len[3];
  double l_1, l_2;
  l_1 = sqrt(890 - 406 * cos(190 - theta_2));
  alpha = (190 - theta_1) * pi / 180;
  beta = (180 - theta_1 + (theta_2 - 20.92)) * pi / 180;
  AB = sqrt(1073 - 448 * cos(beta));
  A_1 = (asin(7.25 * sin(alpha) / AB)) * 180 / pi; //angle a
  k1 = 180 - 60 - A_1;
  k2 = (asin(7 * sin(beta) / AB)) * 180 / pi;
  gamma = k1 + k2 + 60;
  cab = (240 - k1 - k2) * pi / 180 - a ;
  l_2 = sqrt(49 + AB * AB - 14 * cos(cab));
  len[0] = map (l_1, min_1, max_1, 1023, 0);
  len[1] = map (l_2, min_2, max_2, 256, 1023);
  //   Serial.print(theta_1);
  //    Serial.print(" ");
  //     Serial.print(theta_2);
  //  Serial.print(" ");
  //  Serial.print(l_1);
  //  Serial.print(" ");
  //   Serial.println(l_2);
  ////    Serial.print(len[0]);
  return len;
}



void movement(int  L_1, int   L_2)
{
  int m = analogRead(pot_1);
  int n = analogRead(pot_2);
  //Serial.println(pot_1);
  //Serial.print(" ");
  //Serial.println(L_2);
  
  if (L_1 > m+3)
  {
    exp_1();
  }
  else if (L_1 < m-3)
  {
    cont_1();
  }
   else if (L_1 <= m + 3 || L_1 >= m - 3)
  { stop_1();}
  

   if (L_2 < n-3)
  {
    cont_2();
  }
  else if (L_2 > n+3)
  {
    exp_2();
  }
  else  if (L_2 <= n + 3 || L_2 >= n - 3)
  {
    stop_2();
  }
  
 

  Serial.print(L_1); Serial.print(" "); Serial.print(m); Serial.print(" "); Serial.print(L_2); Serial.print(" "); Serial.println(n);
}

void leg_up()
{
  double c1, c2, c3;
  double phi1, phi2, phi3;
  static double *l;
  for (y = 0; y <= (b1 / 2); y = y + 0.1)
  {
    x_1 = 0;
    y_1 = 55 - y;
    OA = sqrt((x_1 * x_1) + (y_1 * y_1));
    //    c1 = (OA*OA+a*a-b*b)/(2*a*OA);
    c2 = (y_1 / x_1);
    //    c3 = (a*a+b*b-OA*OA)/(2*a*b);
    phi1 = (acos((OA * OA + a * a - b * b) / (2 * OA * a))) * 180. / pi;

    phi2 = (atan(c2)) * 180. / pi;
    phi3 = -(acos((a * a + b * b - OA * OA) / (2 * a * b))) * 180. / pi;
    theta_1 = phi1 + phi2;
    theta_2 = phi3 = theta_1 - 180;
    Serial.print(theta_1); Serial.print(" "); Serial.println(theta_2);// Serial.print(" "); Serial.println(phi3);// Serial.print(len[0]); Serial.print(len[0]); Serial.print(len[0]);
    ;    l = length_actuators(theta_1, theta_2);
    movement ( l[0], l[1] );
  }
}
