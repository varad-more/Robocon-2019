//#include<math.h>
double  theta_1;
double theta_2,alpha,beta,a,k1,k2,gamma,cab;
double L_1,L_2,AB;
double* length_actuators (double , double);
double pi = 3.14159;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
double *l;
l=length_actuators(130,45);
Serial.print("l1: ");
Serial.print(l[0]);
Serial.print("   ");
Serial.print("alpha ");
Serial.print(l[2]);
Serial.print("   ");
Serial.print("beta ");
Serial.print(l[3]);
Serial.print("   ");
Serial.print("AB ");
Serial.print(l[4]);
Serial.print("   ");
Serial.print("a ");
Serial.print(l[5]);
Serial.print("   ");
Serial.print("k1 ");
Serial.print(l[6]);
Serial.print("   ");
Serial.print("k2: ");
Serial.print(l[7]);
Serial.print("   ");
Serial.print("gamma: ");
Serial.print(l[8]);
Serial.print("   ");
Serial.print("cab ");
Serial.print(l[9]);
Serial.print("   ");
Serial.print("l2: ");
Serial.println(l[1]);
}

double* length_actuators (double theta_1, double theta_2)
{
//  theta_1=180;
//  theta_2=180;
  static double len[15];
  len[0]=sqrt(890-406*cos(190-theta_2)); 
  alpha=(190-theta_1)*pi/180;
  beta=(180-theta_1+(theta_2-20.92))*pi/180; 
  AB=sqrt(1073-448*cos(beta));
  a= (asin(7.25*sin(alpha)/AB))*180/pi; //angle a
  k1=180-60-a;
  k2=(asin(7*sin(beta)/AB))*180/pi;
  gamma=k1+k2+60;
  cab= (240-k1-k2)*pi/180-a
  
  
  ;
  len[1]=sqrt(49+AB*AB-14*cos(cab));
  len[2]=alpha;
  len[3]=beta;
  len[4]=AB;
  len[5]=a;
  len[6]=k1;
  len[7]=k2;
  len[8]=gamma;
  len[9]=cab;
  
return len;
} 
