#include <ESP8266WiFi.h>

const char* ssid     = "Robocon";
const char* password = "          -_-";
const char* host = "192.168.0.131";


const char startOfNumberDelimiter = '<';
const char endOfNumberDelimiter   = '>';

double l, x, e = 0;
int i = 0;
void setup ()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin (115200);
  Serial.println();
  delay(10);
  Serial.println ("Starting ...");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); //works!

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
}

void processNumber (const long n, int index)
{
  double m  = n / 100;
  if (index == 0)
  {
    l = m ;
  }
  else if (index == 1) {
    x = m;
  }
  else if (index == 2)
  {
    e = m;
  }
  else
  {
  }
}  // end of processNumber

void processInput ()
{
  static long receivedNumber = 0;
  static boolean negative = false;

  byte c = Serial.read ();
  switch (c)
  {

    case endOfNumberDelimiter:
      if (i == 2)
        i = 0;
      else
        i++;
      if (negative)
        processNumber (-receivedNumber, i);
      else
        processNumber (receivedNumber, i);

    // fall through to start a new number
    case startOfNumberDelimiter:
      receivedNumber = 0;
      negative = false;
      break;

    case '0' ... '9':
      receivedNumber *= 10;
      receivedNumber += c - '0';
      break;

    case '-':
      negative = true;
      break;

  } // end of switch
}  // end of processInput

void loop ()
{

  while (Serial.available ())
    processInput ();

  digitalWrite(LED_BUILTIN, HIGH);

  WiFiClient client;

  const int httpPort = 80;
  if (!client.connect(host, httpPort)) { //works!
    Serial.println("connection failed");
    digitalWrite(LED_BUILTIN, LOW);
    return;
  }

  String url = "/streamer/";
  url += "?l=";
  url += String(l);
  url += "&x=";
  url += String(x);
  url += "&e=";
  url += String(e);
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println(client.read());
  delay(30);
} // end of loop
