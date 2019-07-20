int mpu =0;
const char startOfNumberDelimiter = '<';
const char endOfNumberDelimiter   = '>';
int pitch[8]={0,0,0,0,0,0,0,0};
char value[8][8];

void processInput ()
  {
  static long receivedNumber = 0;
  static boolean negative = false;
  byte c = Serial.read ();
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


void setup()
{
      
       noInterrupts();           // disable all interrupts

  TCCR1A = 0;

  TCCR1B = 0;

  TCNT1  = 0;


  OCR1A = 31250;            // compare match register 16MHz/256/2Hz

  TCCR1B |= (1 << WGM12);   // CTC mode

  TCCR1B |= (1 << CS12);    // 256 prescaler 

  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  interrupts();             // enable all interrupts
      Serial.begin(115200);
      Serial1.begin(115200);
      pinMode(LED_BUILTIN,OUTPUT);
      digitalWrite(LED_BUILTIN,LOW);
      delay(1000); 

}


ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine

{

  if(Serial1.available())
  {
        Serial1.write(value[mpu]);
  }

}
void loop()
{
  String temp ="fuck";
  Serial.write(mpu);
  while(!Serial.available());
  digitalWrite(LED_BUILTIN,HIGH);
  while (Serial.available())
    processInput ();
  temp="<"+(String)pitch[mpu]+">";
  temp.toCharArray(value[mpu],temp.length()+1);
    digitalWrite(LED_BUILTIN,LOW);
    //delay(1./200);
    Serial.flush();
    Serial.print(mpu);
    Serial.println(pitch[mpu]);
    mpu++;
    if (mpu==8) mpu=0;
    }
    
