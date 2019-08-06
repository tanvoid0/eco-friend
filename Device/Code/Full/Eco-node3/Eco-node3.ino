// DHT
#include "DHTesp.h"
#define DHTpin D0    //D5 of NodeMCU is GPIO14

// Light
#include <Wire.h>
#include <BH1750FVI.h>

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


void setup() 
{
  Serial.begin(115200);
  LightSensor.begin();  
  dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 17
  Serial.println("Running...");
}

void loop()
{
  // DHT
  delay(dht.getMinimumSamplingPeriod()+500);

  humidity = dht.getHumidity();
  temperature = dht.getTemperature();
  
  
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

  // Light
  uint16_t lux = LightSensor.GetLightIntensity();

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("\tHumd: ");
  Serial.print(humidity);

  
  Serial.print("\tLight: ");
  Serial.print(lux);
  
  Serial.print("\tMoist: ");
  Serial.print(mRes);
  Serial.println("");
  delay(250);
}

void Soil(){
 
  return;
}
