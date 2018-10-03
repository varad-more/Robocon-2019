#include <XBOXRECV.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>


//uint8_t ctrlNumber = 0;

#define m1pwm 50
#define m2pwm 30
#define m3pwm 20
#define m1p1 40
#define m1p2 41
#define m2p1 42
#define m2p2 43
#define m3p1 44
#define m3p2 45

void forward(int);
void backward(int);
void left(int);
void right(int);
void clock_wise(int);
void anti_clock_wise(int);
void hard_brake(int);
void soft_brake();

USB Usb;
XBOXRECV Xbox(&Usb);

void setup()
{
  Serial.begin(115200);
  if (Usb.Init() == -1) {
    Serial.print("OSC did not start");
    while (1);
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
  //  Usb.Init();
  //  Serial.println( "Begin speed log." );
  pinMode(m1p1, OUTPUT);
  pinMode(m1p2, OUTPUT);
  pinMode(m2p1, OUTPUT);
  pinMode(m2p2, OUTPUT);
  pinMode(m3p1, OUTPUT);
  pinMode(m3p2, OUTPUT);

  hard_brake(255);
}
void loop()
{
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t ctrlNumber = 0; ctrlNumber < 4; ctrlNumber++) {
      if (Xbox.Xbox360Connected[ctrlNumber]) {
        int pwm;
        //        Serial.println(Xbox.getAnalogHat(RightHatY, ctrlNumber));
        //left
        if (Xbox.getAnalogHat(RightHatX, ctrlNumber) < 0) {
          pwm = map(Xbox.getAnalogHat(RightHatX, ctrlNumber), -7500, -32768, 0, 255);
          Serial.println("LEFT : " + pwm);
          left(pwm);
        }

        // forward condn
        if (Xbox.getAnalogHat(RightHatY, ctrlNumber) > 0) {
          pwm = map(Xbox.getAnalogHat(RightHatY, ctrlNumber), 7500, 32767, 0, 255);
          //Serial.println("FORWARD : " + pwm);
          forward(pwm);
        }

        //right
        if (Xbox.getAnalogHat(RightHatX, ctrlNumber) > 0) {
          pwm = map(Xbox.getAnalogHat(RightHatX, ctrlNumber), 7500, 32767, 0, 255);
          //Serial.println("RIGHT : " + pwm);
          right (pwm);
        }

        // backward condn
        if (Xbox.getAnalogHat(RightHatY, ctrlNumber) < 0) {
        pwm = map(Xbox.getAnalogHat(RightHatY, ctrlNumber), -7500, -32768, 0, 255);
          //Serial.println("BACKWARD : " + pwm);
          backward(pwm);
        }
      }
    }
  }
}

void forward(int pwm) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, pwm * 0.5);
  analogWrite(m2pwm, pwm * 1.54);
  analogWrite(m3pwm, pwm * 0.5);
}

void backward(int pwm) {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, pwm * 0.866);
  analogWrite(m2pwm, pwm);
  analogWrite(m3pwm, pwm * 0.866);
}

void left(int pwm) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm * 0.866);
  analogWrite(m3pwm, pwm * 0.866);
}

void right(int pwm) {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm * 0.866);
  analogWrite(m3pwm, pwm * 0.866);
}

void clock_wise(int pwm) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm);
  analogWrite(m3pwm, pwm);
}
void anti_clock_wise(int pwm) {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, pwm);
  analogWrite(m2pwm, pwm);
  analogWrite(m3pwm, pwm);
}

void hard_brake(int intensity) {
  digitalWrite(m1p1, HIGH);
  digitalWrite(m1p2, HIGH);
  digitalWrite(m2p1, HIGH);
  digitalWrite(m2p2, HIGH);
  digitalWrite(m3p1, HIGH);
  digitalWrite(m3p2, HIGH);
  analogWrite(m1pwm, intensity);
  analogWrite(m2pwm, intensity);
  analogWrite(m3pwm, intensity);
}

void soft_brake() {
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, LOW);
  digitalWrite(m2p1, LOW);
  digitalWrite(m2p2, LOW);
  digitalWrite(m3p1, LOW);
  digitalWrite(m3p2, LOW);
  analogWrite(m1pwm, 35);
  analogWrite(m2pwm, 35);
  analogWrite(m3pwm, 35);
}
