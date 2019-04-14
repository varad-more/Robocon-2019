#define link1 0
#define link2 1
#define link3 2
#define link4 3

int pointer = 0;
int flag[4] = {0, 0, 0, 0};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.write(0);
  Serial1.write(0);
  Serial2.write(0);
  Serial3.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) flag[link1] = Serial.read();
  if (Serial1.available()) flag[link2] = Serial1.read();
  if (Serial2.available()) flag[link3] = Serial2.read();
  if (Serial3.available()) flag[link4] = Serial3.read();
  if (flag[link1])// && flag[link2] && flag[link3] && flag[link4])
  {
    pointer ++;
    if (pointer == 4) pointer = 0;
    Serial.write(pointer);
    Serial1.write(pointer);
    Serial2.write(pointer);
    Serial3.write(pointer);
  }
}
