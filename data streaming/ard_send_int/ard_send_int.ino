
// Example of sending numbers by Serial
// Author: Nick Gammon
// Date: 31 March 2012

const char startOfNumberDelimiter = '<';
const char endOfNumberDelimiter   = '>';

double info[3];
int sendinfo[3];

void setup ()
{
  Serial1.begin (115200);
  Serial.begin (115200);

  info[0] = 180;
  info[1] = -180;
  info[2] = 90;

  sendinfo[0] = int(info[0] * 100);
  sendinfo[1] = int(info[1] * 100);
  sendinfo[2] = int(info[2] * 100);
  for (int i = 0; i < 3; i++)
    Serial.println(sendinfo[i]);

  } // end of setup

void loop ()
{
  Serial.println ("Starting ...");
  for (int i = 0; i < 3; i++)
  {
    Serial1.print (startOfNumberDelimiter);
    Serial1.print (sendinfo[i]);    // send the number
    Serial1.print (endOfNumberDelimiter);
    Serial1.println ();
  }  // end of for

  delay (2000);
}  // end of loop
