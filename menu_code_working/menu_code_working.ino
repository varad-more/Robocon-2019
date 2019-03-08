//Libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int Button1 = 2; //increment
int Button2 = 3; //decrement
int Button3 = 4; //enter
float variable1, variable2, variable3, variable4;
int i = 1, enter = 0, j = 1;
void code1();
void code2();
void code3();
void code4();
void selectcode();

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address, if it's not working try 0x27.

void setup() {
  Serial.begin(9600);
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);
  pinMode(Button3, INPUT);
  digitalWrite(Button1, LOW);
  digitalWrite(Button2, LOW);
  digitalWrite(Button3, LOW);
  lcd.begin(16, 2);  // iInit the LCD for 16 chars 2 lines
  Serial.println("LCD begin");
  lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
  lcd.setCursor(0,0); //First line
  lcd.print("ROBOCON 2019");
  lcd.setCursor(0, 1); //Second line
  lcd.print("ARC");
  while (enter == 0)
  {
    selectcode();
    Serial.println("Still in setup");
    delay(100);
  }

}

void loop() {
  if (i == 1) code1();
  if (i == 2) code2();
  if (i == 3) code3();
  if (i == 4) code4();
  lcd.clear();
}

void selectcode()
{
  //lcd.setCursor(0, 0);
  lcd.setCursor(0, 1);
  //printcodeno();
  increment_point();
  decrement_point();
  Serial.println("Value of i = ");
  Serial.println(i);
  if (i > 4 || i < 0)
  {
    i = 1;
  }
  printcodeno();
  pressenter();
}
void printcodeno()
{
  if (i == 1)
  {
    lcd.print("code 1");
  }
  if (i == 2)
  {
    lcd.print("code 2");
  }
  if (i == 3)
  {
    lcd.print("code 3");
  }
  if (i == 4)
  {
    lcd.print("code 4");
  }

}
void increment_point()
{
  if (digitalRead(Button1) == HIGH)// && digitalRead(Button2) == LOW && digitalRead(Button3) == LOW )
  {
    i++;
    delay(500);
  }
}
void decrement_point()
{
  if (digitalRead(Button2) == HIGH)//digitalRead(Button1) == LOW && digitalRead(Button2) == HIGH && digitalRead(Button3) == LOW)
  {
    i--;
    delay(500);
  }
}

/*void code1()
  {
  float variable1, variable2, variable3, variable4,variable;
  printvariable(variable1, variable2, variable3, variable4); //print first i th variable
  if (enter == 1)
  {
    increment_var();
    decrement_var();
  }
  if (j > 4 || j < 0)
  {
    j = 1;
  }
  pressenter();
  if (enter == 2)
  {
    variable = increment_var(variable);
    variable = decrement_var(variable);
    printvariable(variable);
    pressenter();
  }


  }
*/
void code1()
{
  lcd.print("Code 1");
}
void code2()
{

  printvariable(variable1, variable2, variable3, variable4); //print first i th variable
  if (enter == 1)
  {
    increment_varpoint();
    decrement_varpoint();
    Serial.print("j =   ");
    Serial.println(j);
  }
  if (j > 4 || j < 0)
  {
    j = 1;
  }
  pressenter();
  if (enter == 2)
  {

    if (j == 1)
    {
      if (digitalRead(Button1) == HIGH)
        variable1 = increment_var(variable1);
      if (digitalRead(Button2) == HIGH)
        variable1 = decrement_var(variable1);
      Serial.print("var 1 =   ");
      Serial.println(variable1);
      printvariable(variable1, variable2, variable3, variable4);
      pressenter();
    }
    if (j == 2)
    {
      variable2 = increment_var(variable2);
      variable2 = decrement_var(variable2);
      printvariable(variable1, variable2, variable3, variable4);
      pressenter();

    }
    if (j == 3)
    {
      variable3 = increment_var(variable3);
      variable3 = decrement_var(variable3);
      printvariable(variable1, variable2, variable3, variable4);
      pressenter();

    }
    if (j == 4)
    {
      variable4 = increment_var(variable4);
      variable4 = decrement_var(variable4);
      printvariable(variable1, variable2, variable3, variable4);
      pressenter();

    }
  }
}

void code3()
{
  lcd.print("Code 3");
}

void code4()
{
  lcd.print("Code 4");
}

void printvariable(float variable1, float variable2, float variable3, float variable4)
{
  lcd.clear();
  if (j == 1)
  {
    lcd.print("variable 1=");
    lcd.print(variable1);
    //Serial.print("var 1 =   ");
    //Serial.println(variable1);
    delay(500);
  }
  if (j == 2)
  {
    lcd.print("variable 2=");
    lcd.print(variable2);
    delay(500);
  }
  if (j == 3)
  {
    lcd.print("variable 3=");
    lcd.print(variable3);
    delay(500);
  }
  if (j == 4)
  {
    lcd.print("variable 4=");
    lcd.print(variable4);
    delay(500);

  }
}
float increment_varpoint()
{
  if (digitalRead(Button1) == HIGH)// && digitalRead(Button2) == LOW && digitalRead(Button3) == LOW )
  {
    j++;
  }
  return j;
}
float decrement_varpoint()
{
  if (digitalRead(Button2) == HIGH)//digitalRead(Button1) == LOW && digitalRead(Button2) == HIGH && digitalRead(Button3) == LOW)
  {
    j--;
  }
  return j;
}
void pressenter()
{
  if (digitalRead(Button3) == HIGH)//digitalRead(Button1) == LOW && digitalRead(Button2) == LOW && digitalRead(Button3) == HIGH)
  {
    enter++;
    Serial.print("enter =   ");
    Serial.println(enter);
    if (enter == 3) enter = 1;
    Serial.println("Enter pressed");
  }
}
float increment_var(float variable)
{
  if (digitalRead(Button1) == HIGH)
  {
    variable ++;
    return (variable);
  }
}
float decrement_var(float variable)
{
  if (digitalRead(Button2) == HIGH)
  {
    variable --;
    return (variable);
  }
}
