/* I2C LCD 16x2 Arduino Tutorial
 * More info http://www.ardumotive.com/i2clcd(en).html
 * Dev: Michalis Vasilakis Date: 19/11/2016 Ver. 1.0 */

//Libraries 
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
int Button1 =2;
int Button2 =3;
int Button3 =4;
int Button4 =5;




LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, if it's not working try 0x27.

void setup(){
  Serial.begin(9600);
  pinMode(Button1,INPUT);
  pinMode(Button2,INPUT);
  pinMode(Button3,INPUT);
  pinMode(Button4,INPUT);
  
  lcd.begin(16,2);   // iInit the LCD for 16 chars 2 lines
  lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
  lcd.setCursor(0,0); //First line
  lcd.print("ROBOCON 2019");
  lcd.setCursor(0,1); //Second line
  lcd.print("ARC");
}

void loop(){
  lcd.setCursor(0,0);
//lcd.print("PROGRAM No:");
lcd.setCursor(0,1);

if (digitalRead(Button1)==HIGH && digitalRead(Button2)==LOW && digitalRead(Button3)==LOW && digitalRead(Button4)==LOW)
{
lcd.print(1);
//Function Call
}

if (digitalRead(Button2)==HIGH && digitalRead(Button1)==LOW && digitalRead(Button3)==LOW && digitalRead(Button4)==LOW)
{
lcd.print(2);
//Function Call
}
if (digitalRead(Button3)==HIGH && digitalRead(Button2)==LOW && digitalRead(Button1)==LOW && digitalRead(Button4)==LOW)
{
lcd.print(3);

//Function Call
}
if (digitalRead(Button4)==HIGH && digitalRead(Button2)==LOW && digitalRead(Button3)==LOW && digitalRead(Button1)==LOW)
{
lcd.print(4);
//Function Call
}
}
