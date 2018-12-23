void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int fb1 = analogRead(A0);
  int fb2 = analogRead(A1);

  //  fb1 = map(fb1, 800, 940, 105, 10);
  //  fb2 = map(fb2, 917, 279, 170, 15);

  Serial.print("  fb1  ");
  Serial.print(fb1);
  Serial.print("  fb2  ");
  Serial.println(fb2);

}
