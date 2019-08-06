
/** Include Starts **/
  // Display 
    #include <SPI.h>               // include SPI library
    #include <Adafruit_GFX.h>      // include adafruit graphics library
    #include <Adafruit_PCD8544.h>  // include adafruit PCD8544 (Nokia 5110) library

  // DHT
    #include "DHTesp.h"
    #define DHTpin D5    //D5 of NodeMCU is GPIO14
    DHTesp dht;

/** Include Ends **/


  // Nokia 5110 
    // LCD module connections (CLK, DIN, D/C, CS, RST)
    Adafruit_PCD8544 display = Adafruit_PCD8544(D4, D3, D2, D1, D0);
    #define NUMFLAKES 10
    #define XPOS 0
    #define YPOS 1
    #define DELTAY 2
    
    #define DHTpin D6
    
    String server_status[] = { "Offline", "Online"};

  // Soil
    const int AirValue = 890;   //you need to replace this value with Value_1
    const int WaterValue = 470;  //you need to replace this value with Value_2
    int intervals = (AirValue - WaterValue)/3;
    int mVal = 0;
    int mPin = A0;
    String mRes = "";

  // DHT
    float humidity = 0;
    float temperature = 0;

void setup()   {
  // DHT
   dht.setup(DHTpin, DHTesp::DHT11);
  Serial.begin(115200);

  // Display
    display.begin();
    display.setContrast(50);
    display.setRotation(2);
    display.display(); // show splashscreen
    delay(2000);
    display.clearDisplay();   // clears the screen and buffer
    display.setTextSize(1);
    display.setTextColor(BLACK);
  
}
void loop() {
  Soil();
  Printer();
  DHT_Function();
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

void DHT_Function(){
  delay(dht.getMinimumSamplingPeriod()+106);

   humidity = dht.getHumidity();
   temperature = dht.getTemperature();
}
void Printer(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Srvr: "+server_status[0]);
  display.println("");
  display.println("Lite: 15 Lux");
  display.print  ("Temp: ");
  Serial.println(temperature);
  display.print(temperature);
  display.print((char)247);
  display.println("C");
  display.print  ("Hum : ");
  display.print(humidity);
  display.println("%");
  display.print("Mst : ");
  display.println(mRes);
  display.display();
//  delay(2000);
}
