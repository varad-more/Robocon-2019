int mpu=0;
int no=0;
int pitch[8];
const char startOfNumberDelimiter = '<';
const char endOfNumberDelimiter   = '>';
void setup() {
  // put your setup code here, to run once:

Serial1.begin(115200);
Serial.begin(115200);
      pinMode(LED_BUILTIN,OUTPUT);
      digitalWrite(LED_BUILTIN,LOW);
}
void processInput ()
  {
  static long receivedNumber = 0;
  static boolean negative = false;
  byte c = Serial1.read ();
  switch (c)
    {
      case endOfNumberDelimiter:  
      if (negative) 
        pitch[mpu]=-receivedNumber; 
      else
        pitch[mpu]=receivedNumber; 

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
      
    }   
  }  
void loop() {
  // put your main code here, to run repeatedly:
Serial1.write(mpu);
  digitalWrite(LED_BUILTIN,LOW);
  while(!Serial1.available());
  digitalWrite(LED_BUILTIN,HIGH);
  while (Serial1.available())
    processInput ();
    delay(100);
    Serial.print(mpu);
    Serial.println(pitch[mpu]);
    mpu++;
    if (mpu==8) mpu=0;
    

}
