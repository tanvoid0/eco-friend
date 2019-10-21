
// DHT
#include "DHTesp.h"
#define DHTpin D0    //D5 of NodeMCU is GPIO14

// Light
#include <Wire.h>
#include <BH1750FVI.h>

// WiFi
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


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

// LIGHT
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


// DHT
DHTesp dht;


// Wifi


// Logo
char bmp1[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xfe, 0x1e, 0x0e, 0x0e, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0xfe, 0xfc, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xfc, 0xff, 0xdf, 0xc0, 0x80, 0xc0, 0xc0, 0xc0, 0x80, 0xc1, 0xc0, 0x80, 0xc0, 0xc0, 0xc0, 0x80, 0xc0, 0x80, 0xc0, 0xc7, 0xff, 0xff, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xcf, 0xdf, 0xdd, 0x8d, 0x9d, 0x8d, 0x9d, 0x8d, 0x9d, 0x8d, 0x8d, 0xfd, 0xfd, 0x9d, 0x9d, 0x8d, 0x9d, 0x8d, 0x9d, 0x8d, 0x8d, 0xdd, 0xcf, 0xdf, 0xcd, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfe, 0xff, 0x87, 0x81, 0x89, 0x8c, 0xce, 0xe7, 0x7b, 0x3f, 0x8f, 0xc1, 0xe1, 0xe1, 0x71, 0x31, 0x31, 0x3f, 0x3f, 0x31, 0x31, 0x71, 0x61, 0xe1, 0xc1, 0x83, 0x3f, 0x7f, 0xf3, 0xce, 0x8e, 0x8d, 0x81, 0x83, 0x8f, 0xfe, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x01, 0x01, 0x03, 0x03, 0x11, 0x01, 0x00, 0x00, 0xfe, 0xff, 0x03, 0x01, 0x00, 0x30, 0x30, 0xb8, 0xbc, 0xfe, 0xf7, 0x73, 0x32, 0x00, 0x00, 0x03, 0xdf, 0xff, 0x78, 0x00, 0x01, 0x01, 0x01, 0x03, 0x03, 0x01, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0f, 0x1c, 0x18, 0x38, 0x73, 0x73, 0x73, 0x71, 0x70, 0x30, 0x30, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Sensor vars
int mVal, lux = 0;
String mRes = "";
float humidity, temperature = 0;

// WiFi vars
String ssid, password, payload, srvr_api;
String host = "http://djangpi.herokuapp.com/api";

String url = "/datalogs/";
int httpCode;
