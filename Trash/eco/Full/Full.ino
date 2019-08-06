#include<SoftwareSerial.h>
SoftwareSerial BT(10, 11);
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x3F, 2,1,0,4,5,6,7,3, POSITIVE);

#include <dht.h>
dht DHT;

#define DHT11_PIN 7

//int lightPin = 0;
const int ldrPin = A0;

int moistPin = 1;

int tmp, lux;
int moist, hmd;
void setup(){
  pinMode(ldrPin, INPUT);
  BT.begin(9600);
  BT.println("Hello from Arduino");
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
}

void loop(){
 
  Light();
  delay(200);
  Temp();
  Moisture();
  delay(1000);
}

void Temp(){
  int chk = DHT.read11(DHT11_PIN);
  tmp = DHT.temperature;
  Print("Temp", tmp, String((char)223)+"C");
  hmd = DHT.humidity;
  Print("Humid", hmd, "%");
  return;
}

void Light(){
  lux = analogRead(ldrPin); // read the value from the sensor
  int ldrStatus= 0;
  if(lux <= 200){
    ldrStatus = 0;
  } else {
    ldrStatus = 1;
  }
  Print("Light", lux, "");
  return;
}

void Moisture(){
   moist= analogRead(moistPin);

   moist = map(moist,550,0,0,100);

   Print("Moist",moist,"%");
}

void Print(String sen, double var, String unit){
  lcd.clear();
//  lcd.print("Home Forestation!");
  lcd.setCursor(0,0);
  lcd.print(sen+": "+String(var)+" "+unit);
  Serial.println(sen+": "+String(var)+" "+unit);
  BT.println(sen+": "+String(var)+" "+unit);
  delay(2000);
}
