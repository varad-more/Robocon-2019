 int T[2]={0,0};
 float a1 = 0;
float a2 = 39;
float a3 = 0;
float a4 = 39;
 
void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
   float r1 = 0;
      float phi1 = 0;
      float phi2 = 0;
      float phi3 = 0;
      
      for(int X=0;X<=20;X++)
      {for (int Y=0;Y>=-55;Y--)
      {
      r1 = sqrt(X * X + Y * Y);
      phi1 = acos(((r1 * r1) + (a2 * a2) - (a4 * a4)) / (2.0 * a2 * r1));
      phi2 = atan(Y / X);
      phi3 = (acos(((a4 * a4) + (a2 * a2) - (r1 * r1)) / (2.0 * a2 * a4)))*180/PI;
      T[0] = (phi2 + phi1)*180/PI;
      T[1] = -(phi3 + T[0] - 180);
      T[1]=T[1]+T[0];
       Serial.print(X);
       Serial.print("  ");
        Serial.print(Y);
        Serial.print("  ");
         Serial.print(T[0]);
         Serial.print("  ");
      Serial.println(T[1]);

   
      
      }
      }
      while(1);
     
}
