double y_o,x_o,x,y,x_1,y_1,OA,a=6,b=2,theta_1,theta_2,pi=3.15159,k1,k2,k3;

void setup() {
Serial.begin(9600);
for(y=0;y<=(b/2);y+=0.1)
  {
   x_1=0;
   y_1=y_o-y;
   OA=sqrt(x_1*x_1+y_1*y_1);
    k1=acos((OA*OA+a*a-b*b)*a*OA/2))*180/pi;
    k2=atan(y_1/x_1)*180/pi;
    k3=acos((a*a+b*b-OA*OA)*a*b/2)*180/pi;
    theta_1=k1+k2;
    theta_2=k3+theta_1-180;
    Serial.print("theta1 ");
    Serial.print(theta_1);
    Serial.print("   ");
    Serial.print("theta2 ");
    Serial.print(theta_2);
    Serial.println("   ");
    }
}

void loop() {

}
