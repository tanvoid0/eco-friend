#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

/* Set these to your desired credentials. */
const char *ssid = "Peace squ";  //ENTER YOUR WIFI SETTINGS
const char *password = "dhaka1207";
const char *host = "192.168.43.161";

String str;
void setup() {
  Serial.begin(9600);
  // Wifi Setup
  WifiSetup();
}
void loop() {
  receiver();
  sendToServer(str);
  delay(2000);
}

void WifiSetup() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void sendToServer(String post) {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;    //Declare object of class HTTPClient
    //http.begin("http://"+String(host)+"/Api/eco-friend/insert.php");      //Specify request destination
//    http.begin("http://" + String(host) + "/Api/eco-friend/insert-csv.php");
    http.begin("http://api-tanveer.herokuapp.com/eco-friend/insert-csv.php");
    http.addHeader("Content-Type", "text/plain"); //Specify content-type header

    int httpCode = http.POST(str); //Send the request
    String payload = http.getString();                  //Get the response payload

    Serial.println(httpCode);   //Print HTTP return code
//    Serial.println(payload);    //Print request response payload

    http.end();  //Close connection

  } else {

//    Serial.println("Error in WiFi connection");

  }

}
void receiver() {
  
  str = Serial.readString();
//  Serial.println(str);
  delay(1000);
}
