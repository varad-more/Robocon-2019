int c_mpu_number = 0;
const char startOfNumberDelimiter = '<';
const char endOfNumberDelimiter   = '>';
int pitch_c[8] = {0, 0, 0, 0, 0, 0, 0, 0};


void processInput_c ()
{
  while(Serial.available()){
  static long receivedNumber = 0;
  static boolean negative = false;
  byte c = Serial.read ();
  switch (c)
  {
    case endOfNumberDelimiter:
      if (negative)
      {
        pitch_c[c_mpu_number] = -receivedNumber;
      }
      else
      {
        pitch_c[c_mpu_number] = receivedNumber;
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
      c_mpu_number = receivedNumber;
      receivedNumber = 0;
      break;
  }
  }
}


void setup()
{
  Serial.begin(115200);
//  Serial1.begin(115200);/
}

void loop()
{ 
  Serial.println("start loop");
  /*while (!Serial.available())
  {
   Serial.println("H");
  }*/
  processInput_c ();   
  /*
  while (Serial.available())
    {
      processInput_c ();   
      Serial.println("  in process  ");
    }*/
    Serial.println("end transmission");
   // Serial.println("endprocess");

  Serial.print(c_mpu_number);Serial.print(":");Serial.println(pitch_c[c_mpu_number]);
 // mpu=0;
  //Serial.println("end loop");
 // Serial.flush();
}
