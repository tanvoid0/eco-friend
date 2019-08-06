#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

/* Set these to your desired credentials. */
const char *ssid = "Peace squad";  //ENTER YOUR WIFI SETTINGS
const char *password = "dhaka1207";

const char *host = "192.168.0.107";

#include <SoftwareSerial.h>
SoftwareSerial s(D6, D5);

char data;
String str;
void setup() {
  Serial.begin(9600);
  s.begin(9600);

  // Wifi Setup
  WifiSetup();
}
void loop() {
  receiver();
  
}

void sendToServer(String post){
  HTTPClient http;    //Declare object of class HTTPClient
 
  http.begin("https://api-tanveer.herokuapp.com/eco-friend/insert.php");//Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
 
  int httpCode = http.POST(post);   //Send the request
  String payload = http.getString();    //Get the response payload

  if(httpCode != 200){
    Serial.println(httpCode);   //Print HTTP return code  
  }
  
  Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection
  
  delay(2000);  //Post Data at every 5 seconds
}

void receiver(){
  s.write("s");
  if (s.available() > 0) {
    str = "";
    do {
      data = s.read();
      if(char(data) == '?'){
        str+= '&';
      }
      else if (char(data) != '?') {
        str += data;
      }
      

      delay(10);
    } while (char(data) != '\n');
  }
  Serial.println(str);
  sendToServer(str);
  delay(500);
}
void WifiSetup() {
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot

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
