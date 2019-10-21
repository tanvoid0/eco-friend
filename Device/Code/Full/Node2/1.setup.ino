void setup() 
{
  Serial.begin(115200);
  LCD_SETUP();
  // Sensors initialize
  LightSensor.begin();  
  dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 17
//  WIFI_SETUP();

  delay(2000);
}
