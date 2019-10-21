#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Fokinnira dure thak";
const char *password = "murikha_sala";

const char *host = "http://djangpi.herokuapp.com";

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
//  HTTPClient http;
//  http.begin(host, NULL, );
//  int httpCode = http.GET();
//  String payload = http.getString();
//  Serial.println(httpCode);
//  Serial.println(payload);
//  http.end();
//  delay(5000);

  WifiClient client;
  const int httpPort = 80;
  if(!client.connect(host, httpPort)){
    Serial.println("Connection failed!");
    return;
  }
  String url = "/api/plants/1";
  client.print(String("GET ")+
    url+
    " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" + 
    "Connection: close\r\n\r\n"
    );
}
