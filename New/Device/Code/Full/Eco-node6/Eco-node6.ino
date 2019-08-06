#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

// WiFi
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// DHT
#include "DHTesp.h"
#define DHTpin D0    //D5 of NodeMCU is GPIO14

// Light
#include <Wire.h>
#include <BH1750FVI.h>

// Display 

 
#include <SPI.h>               // include SPI library
#include <Adafruit_GFX.h>      // include adafruit graphics library
#include <Adafruit_PCD8544.h>  // include adafruit PCD8544 (Nokia 5110) library
// Nokia 5110 LCD module connections (CLK, DIN, D/C, CS, RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(D7, D6, D5, D4, D3);
 
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define PIN_RESET D3
#define PIN_SCE   D4
#define PIN_DC    D5
#define PIN_SDIN  D6
#define PIN_SCLK  D7

#define LCD_X     84
#define LCD_Y     48
#define LCD_C     LOW
#define LCD_D     HIGH

// Settings
uint8_t ADDRESSPIN = 13;
BH1750FVI::eDeviceAddress_t DEVICEADDRESS = BH1750FVI::k_DevAddress_H;
BH1750FVI::eDeviceMode_t DEVICEMODE = BH1750FVI::k_DevModeContHighRes;

// Create the Lightsensor instance
BH1750FVI LightSensor(ADDRESSPIN, DEVICEADDRESS, DEVICEMODE);

// Moist
const int AirValue = 890;   //you need to replace this value with Value_1
const int WaterValue = 470;  //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;
int mPin = A0;
String mRes = "";

// DHT
DHTesp dht;
float humidity;
float temperature;


String srvr_stat[] = { "Offline", "Online"};
String srvr = "";
String srvr_api = "base64:N9UUbuPHAP7SMNJ4ESl4LA1yDzYwc2T5GAG44Rf7R7g=";

// Wifi
/* Set these to your desired credentials. */
char auth[] = "592878cbc70c461f9975b4fb32edf2d1";
const char *ssid = "Password Bolbona";  //ENTER YOUR WIFI SETTINGS
const char *password = "murikha_sala";
int httpCode;
String payload;

//Web/Server address to read/write from 
const char *host = "http://192.168.0.108/LarAPI/public/api/logger";   //https://circuits4you.com website or IP address of server

char bmp1[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xfe, 0x1e, 0x0e, 0x0e, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0xfe, 0xfc, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xfc, 0xff, 0xdf, 0xc0, 0x80, 0xc0, 0xc0, 0xc0, 0x80, 0xc1, 0xc0, 0x80, 0xc0, 0xc0, 0xc0, 0x80, 0xc0, 0x80, 0xc0, 0xc7, 0xff, 0xff, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xcf, 0xdf, 0xdd, 0x8d, 0x9d, 0x8d, 0x9d, 0x8d, 0x9d, 0x8d, 0x8d, 0xfd, 0xfd, 0x9d, 0x9d, 0x8d, 0x9d, 0x8d, 0x9d, 0x8d, 0x8d, 0xdd, 0xcf, 0xdf, 0xcd, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfe, 0xff, 0x87, 0x81, 0x89, 0x8c, 0xce, 0xe7, 0x7b, 0x3f, 0x8f, 0xc1, 0xe1, 0xe1, 0x71, 0x31, 0x31, 0x3f, 0x3f, 0x31, 0x31, 0x71, 0x61, 0xe1, 0xc1, 0x83, 0x3f, 0x7f, 0xf3, 0xce, 0x8e, 0x8d, 0x81, 0x83, 0x8f, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x01, 0x01, 0x03, 0x03, 0x11, 0x01, 0x00, 0x00, 0xfe, 0xff, 0x03, 0x01, 0x00, 0x30, 0x30, 0xb8, 0xbc, 0xfe, 0xf7, 0x73, 0x32, 0x00, 0x00, 0x03, 0xdf, 0xff, 0x78, 0x00, 0x01, 0x01, 0x01, 0x03, 0x03, 0x01, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0f, 0x1c, 0x18, 0x38, 0x73, 0x73, 0x73, 0x71, 0x70, 0x30, 0x30, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
void setup() 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);
  
  LightSensor.begin();  
  dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 17
  Serial.println("Running...");
  display.begin();
  display.setContrast(50);
  display.setRotation(2);
//  display.display(); // show splashscreen
 load_logo();
//  delay(2000);
  display.clearDisplay();   // clears the screen and buffer
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
//  display.print("Connecting.");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
    Serial.print(".");
    display.print(".");
    loading_animation();
//    display.display();
  }
  delay(500);
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP


  display.clearDisplay();   // clears the screen and buffer
  display.setCursor(0,0);
  display.println("Connected to: ");
  display.println("   "+String(ssid));
  display.println("IP Address: ");
  display.print("   ");
  display.println(WiFi.localIP());
  display.display();
  delay(2000);
  
}

void loop()
{
  Blynk.run();
  String ADCData, station, postData;
  
  // Moist
   int mVal = analogRead(mPin);
  if(mVal > WaterValue && mVal < (WaterValue + intervals)) {
    mRes = "Very Wet";
  }
  else if(mVal > (WaterValue + intervals) && mVal < (AirValue - intervals)) {
    mRes = "Wet";
  }
  else if(mVal < AirValue && mVal > (AirValue - intervals)) {
    mRes = "Dry";
  }  
  
  // DHT
//  delay(dht.getMinimumSamplingPeriod()+500);

  humidity = dht.getHumidity();
  temperature = dht.getTemperature();
  


  // Light
  uint16_t lux = LightSensor.GetLightIntensity();
  postData = "";
//  postData = "?api="+srvr_api+"&light="+String(lux)+"&temperature="+String(temperature)+"&humidity="+String(humidity)+"&soil="+mRes+"&moisture="+mVal+"&remarks=";
  postData = "?api="+srvr_api+"&light="+String(lux)+"&temperature="+String(temperature)+"&humidity="+String(humidity)+"&soil="+mRes+"&moisture="+mVal+"&remarks=";
  Serial.println("Request Check: "+postData);
  HTTPClient http;    //Declare object of class HTTPClient
  http.begin(host+postData);              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

  httpCode = http.GET();   //Send the request
  payload = http.getString();    //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  
  htChecker();
  Serial.println(payload);    //Print request response payload
  http.end();  //Close connection




  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("\tHumd: ");
  Serial.print(humidity);

  
  Serial.print("\tLight: ");
  Serial.print(lux);
  
  Serial.print("\tMoist: ");
  Serial.print(mRes);
  Serial.println("");

  display.clearDisplay();
  
  display.setCursor(0,0);
//  display.println("00/00 00:00:00");
  display.println(payload);
  display.println("Srvr: "+ srvr);
  display.println("Lite: "+String(lux)+"    Lx");
  
  display.print("Temp: ");
  display.print(temperature);
  display.print(" ");
  display.print((char)247);
  display.println("C");

  display.print("Humd: ");
  
  display.print(humidity);
  display.println("  %");
  
  display.print("Soil: ");
  display.println(mRes);
  display.display();
  delay(1000);
  
}

void htChecker(){
 if(httpCode == 200){
    srvr = "Online";
  }
  else {
    payload = "HTTP "+httpCode;
    srvr = srvr_stat[0];
    if(httpCode == 400){
      srvr = "Bad Req.";
    }
    else if(httpCode == 401){
      srvr = "Unauth.";
    }
    else if(httpCode == 403){
      srvr = "Forbid.";
    }
    else if(httpCode == 404){
      srvr = "Not Found";
    }
  }
  return;
}

void LcdClear(void)
{
  for (int index = 0; index < LCD_X * LCD_Y / 8; index++)
  {
    LcdWrite(LCD_D, 0x00);
  }
  
  display.setRotation(2);
}

void LcdInitialise(void)
{
  pinMode(PIN_SCE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
  LcdWrite(LCD_C, 0x21 );  // LCD Extended Commands.
  LcdWrite(LCD_C, 0xB1 );  // Set LCD Vop (Contrast). 
  LcdWrite(LCD_C, 0x04 );  // Set Temp coefficent. //0x04
  LcdWrite(LCD_C, 0x14 );  // LCD bias mode 1:48. //0x13
  LcdWrite(LCD_C, 0x0C );  // LCD in normal mode.
  LcdWrite(LCD_C, 0x20 );
  LcdWrite(LCD_C, 0x0C );
}

void gotoXY(int x, int y)
{
  LcdWrite( 0, 0x80 | x);  // Column.
  LcdWrite( 0, 0x40 | y);  // Row. 

}
void LcdWrite(byte dc, byte data)
{
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_SCE, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}

void LcdBitmap(char my_array[]){
  for (int index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++){
    display.setRotation(2);
    LcdWrite(LCD_D, my_array[index]);
  }
}

void load_logo(){
  LcdInitialise();
  LcdClear();
  gotoXY(0,0);
  LcdBitmap(bmp1);
  delay(5000);
}

void loading_animation()
{
  //loading screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);          //set text color, only BLACK or WHITE is to be used
  display.setCursor(8,8);
  display.print("Eco Friend");
  display.setCursor(0,20);
  display.println("Connecting");
  display.print("to Server...");
  display.write(3);
  display.drawRect(0,40,84,5,BLACK);    //draw a rectangle
  display.display();
  for (int l=0;l<85;l++)
  {
    display.fillRect(0,40,l,5,BLACK);   //color the rectangle
    delay(40);
    display.display();
  }
  display.clearDisplay();
}
