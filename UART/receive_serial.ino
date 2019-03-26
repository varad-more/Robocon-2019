volatile int n=0,error, bearing;
volatile char t;
int c=0;
int var=0;
void setup(){
  Serial.begin(115200);
}
void loop(){
 
  while(Serial.available() > 0) // While there is still data
   {
   t = Serial.read(); // Read next character

 
if (t == '-')
{
c =1;
  }

//else if (t == 46)
//{
//  Serial.println ("END");
//  continue;

//  }
else if( t == ',')
{
  if (c==1)
  {  n=-n; // for -ve vals
  c=0; // signed counter
 
  }

  if (var == 0) // for segregatting variables
  {
    error= n;
    var ++;
  // Serial.println( error);
 
  }
  else{
    bearing = n;
    var--;
   // Serial.println(bearing);
}
 
    //Serial.println(n);
   n=0;
}
else if( t == ' ')
 n=0;

else{
  
 n *= 10;
     n += t-48;   
   //  Serial.println(n); 
     }
}
}
    
