//#include <LiquidCrystal_I2C.h>
#include <Wire.h>
//LiquidCrystal_I2C lcd(0x3F, 2,1,0,4,5,6,7,3, POSITIVE);

#include <dht.h>
dht DHT;

#define DHT11_PIN 7

int lightPin = 0;
int moistPin = 1;

int tmp, lux;
int moist, hmd;
void setup(){
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(9600);
//  lcd.begin(16,2);
//  lcd.clear();
}

void loop(){
  Light();
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
  lux = analogRead(lightPin); // read the value from the sensor
  Print("Light", lux, "");
  return;
}

void Moisture(){
   moist= analogRead(moistPin);

   moist = map(moist,550,0,0,100);

   Print("Moist",moist,"%");
}

void Print(String sen, double var, String unit){
//  lcd.clear();
//  lcd.print("Home Forestation!");
//  lcd.setCursor(0,1);
//  lcd.print(sen+": "+String(var)+" "+unit);
  Serial.println(sen+": "+String(var)+" "+unit);
  delay(2000);
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    Serial.print(c);           /* print the character */
  }
 Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
 // Wire.write("Hello NodeMCU");  /*send string on request */
 Wire.write(tmp);
}
