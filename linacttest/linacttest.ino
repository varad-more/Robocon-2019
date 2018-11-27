#include "Timer.h"

Timer t;

int ledEvent;
int pin1 = 6;
int pin2 = 7;
float up = 40;
float down = 40;
float fl_sec_up = 1000 * (up / 30);
int sec_up = ceil(fl_sec_up);
float fl_sec_down = 1000 * (down / 30);
int sec_down = ceil(fl_sec_down);
int afterEvent;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  goup();
  delay(2000);
  godown();
}

void loop() {
  // put your main code here, to run repeatedly:
  t.update();
}

void goup()
{
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  afterEvent = t.every(sec_up, doAfter);//doAfter);
}

void godown()
{
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  afterEvent = t.every(sec_down, doAfter);
}

void doAfter()
{
  digitalWrite(pin2, HIGH);
  digitalWrite(pin1, HIGH);
  
}
