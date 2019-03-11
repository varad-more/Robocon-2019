void setup() {
  // put your setup code here, to run once:
  pinMode(23,OUTPUT);
  pinMode(25,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(29,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
for(int i = 23; i<=30;i++)
{
  if(i % 2 == 0)
    continue;
  if(i == 30)
      i = 23;
  Serial.println(i);
  digitalWrite(i,LOW);
  delay(1000);
  digitalWrite(i,HIGH);
 }
}
