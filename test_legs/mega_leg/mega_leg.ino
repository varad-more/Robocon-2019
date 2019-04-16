#define link1 0
#define link2 1
#define link3 2
#define link4 3

int pointer = 0;
int flag[4] = {0, 0, 0, 0};
void setup() {
  //pinMode(0,OUTPUT);pinMode(1,OUTPUT);pinMode(14,OUTPUT);pinMode(15,OUTPUT);pinMode(16,OUTPUT);pinMode(17,OUTPUT);pinMode(18,OUTPUT);pinMode(19,OUTPUT);
 // digitalWrite(0,HIGH);digitalWrite(1,HIGH);digitalWrite(14,HIGH);digitalWrite(15,HIGH);digitalWrite(16,HIGH);digitalWrite(17,HIGH);digitalWrite(18,HIGH);digitalWrite(19,HIGH);
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
//  Serial.write(0);
//  Serial1.write(0);
//  Serial2.write(0);
//  Serial3.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("flag 1 ");
  if (Serial.available()>0) 
  {flag[link1] = Serial.read();
  //Serial.println(flag[link1]);
  }
  //Serial.println("flag 2 ");
  if (Serial1.available()>0) 
  {flag[link2] = Serial.read();
  //Serial.println(flag[link2]);
  }
  //Serial.println("flag 3 ");
  if (Serial2.available()>0) 
  {  
  flag[link3] = Serial.read();
  //Serial.println(flag[link3]);
  
  }
  //Serial.println("flag 4 ");
  if (Serial3.available()>0) 
  {
     
  flag[link1] = Serial.read();
  //Serial.println(flag[link1]);
  
  }
  //Serial.print(pointer);
  //Serial.print("            " );
  //Serial.print(flag[link1]);Serial.print(" " );Serial.print(flag[link2]);Serial.print(" " );Serial.print(flag[link3]);Serial.print(" " );Serial.println(flag[link4]);
  if (flag[link1]==2 )//&& flag[link2]==2 && flag[link3]==2 && flag[link4])
  {
    pointer ++;
    if (pointer == 4) pointer = 0;
    Serial.write(pointer);
    Serial1.write(pointer);
    Serial2.write(pointer);
    Serial3.write(pointer);
    flag[link1]==1; 
    flag[link2]==1; 
    flag[link3]==1; 
    flag[link4]==1; 
    delay(1000);
  }
 
}
