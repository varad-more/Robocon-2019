#include <XBOXRECV.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXRECV Xbox(&Usb);

void setup() {
  Serial.begin(115200);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
}


void loop() {
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
//        Serial.println(i);

        if (Xbox.getButtonPress(L2, i)) {
          Serial.print("L2: ");
          Serial.print(Xbox.getButtonPress(L2, i));
        }

        if (Xbox.getButtonPress(R2, i)) {
          Serial.print("R2: ");
          Serial.println(Xbox.getButtonPress(R2, i));
        }



        //
        //        if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500) {
        //          Serial.print(F("LeftHatX: "));
        //          Serial.print(Xbox.getAnalogHat(LeftHatX, i));
        //          Serial.print("\t");
        //        }

        //
        //        if (Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500) {
        //          Serial.print(F("LeftHatY: "));
        //          Serial.print(Xbox.getAnalogHat(LeftHatY, i));
        //          Serial.print("\t");
        //        }


        //
          Serial.println(Xbox.getAnalogHat(RightHatX, i) / 131);

        if (Xbox.getAnalogHat(RightHatX, i) > 7500) {
          // Serial.print(F("RightHatX: "));
          Serial.println(Xbox.getAnalogHat(RightHatX, i) / 131);
        }

        //
        if (Xbox.getAnalogHat(RightHatY, i) < -7500) {
          // Serial.print(F("RightHatY: "));
          Serial.println(Xbox.getAnalogHat(RightHatY, i) / 131);
        }

        if (Xbox.getAnalogHat(RightHatY, i) > 7500) {
          // Serial.print(F("RightHatY: "));
          Serial.println(Xbox.getAnalogHat(RightHatY, i) / 131);
        }

        if (Xbox.getButtonClick(UP, i)) {
//          Xbox.setLedOn(LED1, i);
          Serial.println(F("Up"));
        }
        if (Xbox.getButtonClick(DOWN, i)) {
//          Xbox.setLedOn(LED4, i);
          Serial.println(F("Down"));
        }
        if (Xbox.getButtonClick(LEFT, i)) {
//          Xbox.setLedOn(LED3, i);
          Serial.println(F("Left"));
        }
        if (Xbox.getButtonClick(RIGHT, i)) {
//          Xbox.setLedOn(LED2, i);
          Serial.println(F("Right"));
        }

        if (Xbox.getButtonClick(START, i)) {
//          Xbox.setLedMode(ALTERNATING, i);
          Serial.println(F("Start"));
        }
        if (Xbox.getButtonClick(BACK, i)) {
//          Xbox.setLedBlink(ALL, i);
          Serial.println(F("Back"));
        }
        if (Xbox.getButtonClick(L3, i))
          Serial.println(F("L3"));
        if (Xbox.getButtonClick(R3, i))
          Serial.println(F("R3"));

        if (Xbox.getButtonClick(L1, i))
          Serial.println(F("L1"));
        if (Xbox.getButtonClick(R1, i))
          Serial.println(F("R1"));
        if (Xbox.getButtonClick(XBOX, i)) {
          Xbox.setLedMode(ROTATING, i);
          Serial.print(F("Xbox (Battery: "));
          Serial.print(Xbox.getBatteryLevel(i)); // The battery level in the range 0-3
          Serial.println(F(")"));
        }
        if (Xbox.getButtonClick(SYNC, i)) {
          Serial.println(F("Sync"));
          Xbox.disconnect(i);
        }

        if (Xbox.getButtonClick(A, i))
          Serial.println(F("A"));
        if (Xbox.getButtonClick(B, i))
          Serial.println(F("B"));
        if (Xbox.getButtonClick(X, i))
          Serial.println(F("X"));
        if (Xbox.getButtonClick(Y, i))
          Serial.println(F("Y"));
      }
    }
  }
}
