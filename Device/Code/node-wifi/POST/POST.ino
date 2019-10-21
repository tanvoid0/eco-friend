#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Fokinnira dure thak";
const char *password = "murikha_sala";

const String host = "http://djangpi.herokuapp.com/api";

void setup(){
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.begin(ssid, password);
  Serial.print("Connecting...");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected");
}
void loop(){
  
  HTTPClient http;
  String data = "light=1&temperature=2&humidity=3&soil=4&moisture=5&remarks=6"; 
  http.begin(host+"/datalogs/");
  
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(data);
  String payload = http.getString();
  Serial.println(httpCode);
  Serial.println(payload);
  http.end();
  delay(5000);
}
