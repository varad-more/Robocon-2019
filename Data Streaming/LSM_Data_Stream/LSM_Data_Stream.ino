#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "abhijit";
const char* password = "mohan@123";

float Heading;
float Gx;
float Gy;
float Gz;
float Ax;
float Ay;
float Az;
float Mx;
float My;
float Mz;

String heading = String();
String gx = String();
String gy = String();
String gz = String();
String ax = String();
String ay = String();
String az = String();
String mx = String();
String my = String();
String mz = String();

String request;

void setup () {

  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }

}


void loop() {

  heading = Heading * 10000;
  gx = int(Gx * 10000);
  gy = int(Gy * 10000);
  gz = int(Gz * 10000);
  ax = int(Ax * 10000);
  ay = int(Ay * 10000);
  az = int(Az * 10000);
  mx = int(Mx * 10000);
  my = int(My * 10000);
  mz = int(Mz * 10000);

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient
    request = "http://192.168.0.101/esp/?Heading=" + heading + "&Gx=" + gx + "&Gy=" + gy + "&Gz=" + gz + "&Ax=" + ax + "&Ay=" + ay + "&Az=" + az + "&Mx=" + mx + "&My=" + my + "&Mz=" + mz;
    http.begin(request);         //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request

    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload

    }

    http.end();   //Close connection

  }

  delay(500);    //Send a request every 30 seconds

}

