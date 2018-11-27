int distance = 50;
int period = map(distance, 0, 150, 0, 5000);
unsigned long time_now = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (millis() > time_now + period) {
    time_now = millis();
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    Serial.println("Done");
  }
  


}
