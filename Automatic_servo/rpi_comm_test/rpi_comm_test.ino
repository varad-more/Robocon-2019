int mpu = 0;
const char startOfNumberDelimiter = '<';
const char endOfNumberDelimiter   = '>';
int pitch[8] = {0, 0, 0, 0, 0, 0, 0, 0};
char value[8][8];
String temp = "fuck";
void processInput ()
{
  static long receivedNumber = 0;
  static boolean negative = false;
  byte c = Serial.read ();
  switch (c)
  {
    case endOfNumberDelimiter:
      if (negative)
      {
        pitch[mpu] = -receivedNumber;
       
      }
      else
      {
        pitch[mpu] = receivedNumber;
    
  }
        break;
    // fall through to start a new number
    case startOfNumberDelimiter:
      receivedNumber = 0;
      negative = false;
      break;

    case '-':
      negative = true;
      break;

    case '0' :    case '1':    case '2':    case '3':    case '4':    case '5':    case '6':    case '7':    case '8':    case '9':
      receivedNumber *= 10;
      receivedNumber += c - '0';
      break;

    case ':' :
      mpu = receivedNumber;
      receivedNumber = 0;
      break;
     
 
  }
}


void setup()
{
  Serial.begin(115200);
}

void loop()
{ //Serial.println("start loop");
  while (Serial.available())
    {
      processInput ();   
      //Serial.println("receving data");
    }

  Serial.print(0);Serial.print(":");Serial.print(pitch[0]);Serial.print("|");
  Serial.print(1);Serial.print(":");Serial.print(pitch[1]);Serial.print("|");
  Serial.print(2);Serial.print(":");Serial.print(pitch[2]);Serial.print("|");
  Serial.print(3);Serial.print(":");Serial.print(pitch[3]);Serial.print("|");
  Serial.print(4);Serial.print(":");Serial.print(pitch[4]);Serial.print("|");
  Serial.print(5);Serial.print(":");Serial.print(pitch[5]);Serial.print("|");
  Serial.print(6);Serial.print(":");Serial.print(pitch[6]);Serial.print("|");
  Serial.print(7);Serial.print(":");Serial.print(pitch[7]);Serial.println();

}
