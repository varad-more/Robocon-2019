double  theta_1;
double theta_2,alpha,beta,a,k1,k2,gamma,cab;
double L_1,L_2,AB;
double* length_actuators (double , double);
double pi = 3.14159;
double max_1=30;
double max_2=44;
double disp_1,disp_2;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
double *l;
l=length_actuators(135,45);
Serial.print("l1: ");
Serial.print(l[0]);
Serial.print("   ");
Serial.print("l2: ");
Serial.println(l[1]);
disp_1=max_1-l[0];
disp_2=max_2-l[1];


}

void loop() {
  // put your main code here, to run repeatedly:

}

double* length_actuators (double theta_1, double theta_2)
{
  static double len[15];
  len[0]=sqrt(890-406*cos(190-theta_2)); 
  alpha=(190-theta_1)*pi/180;
  beta=(180-theta_1+(theta_2-20.92))*pi/180; 
  AB=sqrt(1073-448*cos(beta));
  a= (asin(7.25*sin(alpha)/AB))*180/pi; //angle a
  k1=180-60-a;
  k2=(asin(7*sin(beta)/AB))*180/pi;
  gamma=k1+k2+60;
  cab= (240-k1-k2)*pi/180-a ;
  len[1]=sqrt(49+AB*AB-14*cos(cab));  
return len;
} 
