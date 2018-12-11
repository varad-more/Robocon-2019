
double Y0=55.15;  //Determined by homogeous transform matrix at Theta1=135 and Theta2=45
double X0=0.0;
double x,y,X,Y,OA;
double a=39;
double b=39;
double Theta1,Theta2,k1,k2,k3;
double pi=3.14159;
double a1=20;
double b1=10; 
void setup() {
Serial.begin(9600);

for(y=0;y<=b1/2;y=y+0.1) // Following Vertical Path 1-2
{
  X=0;
  Y=Y0-y;
  OA=sqrt(X*X+Y*Y);
  k1=(acos((OA*OA+a*a-b*b)/(2*a*OA)))*180./pi;
  k2=(atan(Y/X))*180/pi;
  k3=(acos((a*a+b*b-OA*OA)/(2*a*b)))*180./pi;
  Theta1=k1+k2;
  Theta2= k3+Theta1-180;
  Serial.print("OA=");
  Serial.println(OA);
  Serial.print("Theta 1=");
  Serial.println(Theta1);
  Serial.print("Theta 2=");
  Serial.println(Theta2);
  Serial.println();
}

}

void loop() {
  // Following Path 2-3
  for(y=b1/2;y>=0;y=y-0.1)
  {
   x=(a1/b1)*(sqrt(b1*b1-y*y));
   X=X0+x;
   Y=Y0-y;
  OA=sqrt(X*X+Y*Y);
  k1=(acos((OA*OA+a*a-b*b)/(2*a*OA)))*180./pi;
  k2=(atan(Y/X))*180/pi;
  k3=(acos((a*a+b*b-OA*OA)/(2*a*b)))*180./pi;
  Theta1=k1+k2;
  Theta2= k3+Theta1-180;
  Serial.print("OA=");
  Serial.println(OA);
  Serial.print("Theta 1=");
  Serial.println(Theta1);
  Serial.print("Theta 2=");
  Serial.println(Theta2);
  Serial.println();
   }
   //Following Path 3-4
   for(y=0;y>=-b1/2;y=y-0.1)
  {
   x=(a1/b1)*(sqrt(b1*b1-y*y));
   X=X0+x;
   Y=Y0-y;
  OA=sqrt(X*X+Y*Y);
  k1=(acos((OA*OA+a*a-b*b)/(2*a*OA)))*180./pi;
  k2=(atan(Y/X))*180/pi;
  k3=(acos((a*a+b*b-OA*OA)/(2*a*b)))*180./pi;
  Theta1=k1+k2;
  Theta2= k3+Theta1-180;
  Serial.print("OA=");
  Serial.println(OA);
  Serial.print("Theta 1=");
  Serial.println(Theta1);
  Serial.print("Theta 2=");
  Serial.println(Theta2);
  Serial.println();
   }
   //Following Path 4-5
    for(y=-b1/2;y<=0;y=y+0.1)
  {
   x=(a1/b1)*(sqrt(b1*b1-y*y));
   X=X0+x;
   Y=Y0-y;
  OA=sqrt(X*X+Y*Y);
  k1=(acos((OA*OA+a*a-b*b)/(2*a*OA)))*180./pi;
  k2=(atan(X/Y))*180/pi;
  k3=(acos((a*a+b*b-OA*OA)/(2*a*b)))*180./pi;
  Theta1=90+k1+k2;
  Theta2= k3+Theta1-180;
  Serial.print("OA=");
  Serial.println(OA);
  Serial.print("Theta 1=");
  Serial.println(Theta1);
  Serial.print("Theta 2=");
  Serial.println(Theta2);
  Serial.println();
   }
   // Following path 5-1
    for(y=0;y<=b1/2;y=y+0.1)
  {
   x=(a1/b1)*(sqrt(b1*b1-y*y));
   X=X0+x;
   Y=Y0-y;
  OA=sqrt(X*X+Y*Y);
  k1=(acos((OA*OA+a*a-b*b)/(2*a*OA)))*180./pi;
  k2=(atan(X/Y))*180./pi;
  k3=(acos((a*a+b*b-OA*OA)/(2*a*b)))*180./pi;
  Theta1=90+k1+k2;
  Theta2= k3+Theta1-180;
  Serial.print("OA=");
  Serial.println(OA);
  Serial.print("Theta 1=");
  Serial.println(Theta1);
  Serial.print("Theta 2=");
  Serial.println(Theta2);
  Serial.println();
   }
}
