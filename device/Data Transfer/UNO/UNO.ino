// Libraries
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

#include <dht.h>
dht DHT;
// Pin setup

#define DHT11_PIN 7                                      // DHT
const int ldrPin = A0;                                  // LDR
int moistPin = A1;                                      // Soil Moisture

int tmp, lux, moist, hmd = 0;                           // Initial variables for sensor
String light = "";

/* Serial lists
    UNO Serial 115200
    Node Serial 9600
*/

void setup() {
  // Pinsetup
  pinMode(ldrPin, INPUT);
  // DHT & Soil moisture sensore doesn't need pin setup

  // Own Serial
  Serial.begin(9600);

  // Boot msg
  lcd.begin();
  lcd.backlight();
  Serial.print("Device Booting");
  lcd.print("Device Booting");

  for (int i = 0; i < 5; i++) {
    Serial.print(".");
    lcd.print(".");
    delay(500);
  }
  lcd.clear();
  Serial.println();
}

void loop() {
  Light();
  Temp();
  Moist();
  transmitter();
  Print();
}

void Light() {
  lux = analogRead(ldrPin); // read the value from the sensor
  if(lux > 300){
    light = "HIGH";
  } else {
    light = "LOW";
  }
  return;
}

void Temp() {
  int chk = DHT.read11(DHT11_PIN);
  tmp = DHT.temperature;
  hmd = DHT.humidity;
  return;
}

void Moist() {
  moist = analogRead(moistPin);
  //   moist = map(moist,550,0,0,100);
  moist = (100 - ((moist / 1023.00) * 100));
}

void transmitter() {
  String data = "h=" + String(hmd) + "&m=" + String(moist) + "&l=" + String(light) + "&t=" + String(tmp) + "\n";
  Serial.println(data);
}
void Print() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Eco Friend");
  lcd.setCursor(0, 1);
  lcd.print("Temperature:" + String(tmp) + ((char)223)+"c");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Eco Friend");
  lcd.setCursor(0,1);
  lcd.print("Light: " + String(lux)+"("+light+")");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Eco Friend");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: " + String(hmd) + "%");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Eco Friend");
  lcd.setCursor(0,1);
  lcd.print("Soil Moist: " + String(moist)+"%");
  delay(1000);
}
