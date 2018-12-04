

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "LeMax2";  //ENTER YOUR WIFI SETTINGS
const char *password = "12345679";
const char *host = "192.168.43.128";
const char *port = "80";

double heading = 0;
double vector = 0;

void setup() {
  delay(500);
  digitalWrite(HIGH,LED_BUILTIN);
  Serial.begin(115200);     // Initialize the Serial interface with baud rate of 9600
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(500);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

// the loop function runs over and over again forever
void loop() {

  else
  {
    Serial.println("Hello World..."); //Print Hello word every one second
    delay(1000);                      // Wait for a second
  }
}
