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
        pitch[mpu] = -receivedNumber;
      else
        pitch[mpu] = receivedNumber;
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
  Serial1.begin(115200);
}

void loop()
{
  while (!Serial.available());
  while (Serial.available())
    processInput ();
  temp = "<" + (String)mpu + ":" + (String)pitch[mpu] + ">";
  temp.toCharArray(value[mpu], temp.length()+1);
  Serial1.write(value[mpu]);
  Serial.print(mpu);Serial.println(pitch[mpu]);
}
