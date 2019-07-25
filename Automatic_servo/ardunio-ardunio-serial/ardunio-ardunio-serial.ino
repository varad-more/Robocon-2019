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
  byte c = Serial1.read ();
 // Serial.print("c   ");Serial.println(c);
  switch (c)
  {
    case endOfNumberDelimiter:
      if (negative)
      {
        pitch[mpu] = -receivedNumber;
         Serial.print(mpu);Serial.print(":");Serial.println(pitch[mpu]);
        }
      else
      {
        pitch[mpu] = receivedNumber;
   Serial.print(mpu);Serial.print(":");Serial.println(pitch[mpu]);
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
   //Serial.print("no:   ");Serial.println(receivedNumber);
}


void setup()
{
  Serial1.begin(115200);
  Serial.begin(115200);
}

void loop()
{ Serial.println("start loop");
  while (!Serial1.available());
  while (Serial1.available())
    {processInput ();
   // Serial.println("  in process  ");
    }
    Serial.println("end transmission");
   // Serial.println("endprocess");

  Serial.print(mpu);Serial.print(":");Serial.println(pitch[mpu]);
Serial.println("end loop");
Serial.flush();
}
