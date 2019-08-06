// BH1750
#include <Wire.h>
#include <BH1750FVI.h>

// DHT
#include "DHTesp.h"
#define DHTpin D0    //D5 of NodeMCU is GPIO14
DHTesp dht;
float humidity;
float temperature;


// Moist
const int AirValue = 890;   //you need to replace this value with Value_1
const int WaterValue = 470;  //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;
int mVal = 0;
int mPin = A0;
String mRes = "";

// Light
// Settings
uint8_t ADDRESSPIN = 13;
BH1750FVI::eDeviceAddress_t DEVICEADDRESS = BH1750FVI::k_DevAddress_H;
BH1750FVI::eDeviceMode_t DEVICEMODE = BH1750FVI::k_DevModeContHighRes;

// Create the Lightsensor instance
BH1750FVI LightSensor(ADDRESSPIN, DEVICEADDRESS, DEVICEMODE);

uint16_t lux;
void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("Humidity (%)\tTemperature (C)\tMoisture\tLight");
  // use this instead: 
  dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 17
  LightSensor.begin();  
  
}

void loop()
{
  Soil();
  DHTFunc();

//  Serial.print(dht.getStatusString());
//  Serial.print("\t");
//  Serial.print(dht.getMinimumSamplingPeriod());
//  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.print(mRes);
  Serial.print("\t\t");
  Serial.print(lux, 1);
//  Serial.print("\t\t");
//  Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);
  Serial.println("");
}

void Light(){
  lux = LightSensor.GetLightIntensity();
}

void DHTFunc(){
//  delay(dht.getMinimumSamplingPeriod()+106);
  delay(dht.getMinimumSamplingPeriod()+500);

  humidity = dht.getHumidity();
  temperature = dht.getTemperature();
}
void Soil(){
  mVal = analogRead(mPin);
  if(mVal > WaterValue && mVal < (WaterValue + intervals)) {
    mRes = "Very Wet";
  }
  else if(mVal > (WaterValue + intervals) && mVal < (AirValue - intervals)) {
    mRes = "Wet";
  }
  else if(mVal < AirValue && mVal > (AirValue - intervals)) {
    mRes = "Dry";
  }
  return;
}
