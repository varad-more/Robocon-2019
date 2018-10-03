#inlcude <PS2X_lib.h>
PS2X p_stick;
int p_stick_error=0;
int p_stick_type=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(57600);
p_stick_error=p_stick.config_gamepad(13,12 ,11 ,12 ,true,true); //setting the pins console on arduino  (clk,cmd,att,data,pres,rumble) 

 if (p_stick_error=0)
 


void loop() {
  // put your main code here, to run repeatedly:

}
