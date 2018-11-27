#include <Servo.h>
String receivedChar;
Servo s1;
Servo s2;

void setup() {
  Serial.begin(9600);
  s1.attach(9);
  s2.attach(10);
  s1.write(0);
  s2.write(0);

}

void loop() {
  if (Serial.available() > 0) {
    receivedChar = Serial.readString();
    Serial.print(receivedChar.substring(0, 2));
    Serial.print(",");
    Serial.println(receivedChar.substring(2));
    String pos = receivedChar.substring(2);
    if (receivedChar.substring(0, 2) == "s1")
    {
      s1.write(pos.toInt());
    }
    else if (receivedChar.substring(0, 2) == "s2")
    {
      s2.write(pos.toInt());
    }
  }
}
