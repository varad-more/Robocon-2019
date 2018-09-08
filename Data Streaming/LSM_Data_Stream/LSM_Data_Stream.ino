#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "J7";
const char* password = "asasasas";

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

char request[35];

void setup () {

  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }

}


void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient
    request = "http://192.168.0.101/esp/?Heading=" + Heading + "&Gx=" + Gx + "&Gy=" + Gy + "&Gz=" + Gz + "&Ax=" + Ax + "&Ay=" + Ay + "&Az=" + Az + "&Mx=" + Mx + "&My=" + My + "&Mz=" + Mz;
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
