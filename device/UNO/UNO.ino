// Libraries
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>
dht DHT;


// Pin setup
LiquidCrystal_I2C lcd(0x3F, 2,1,0,4,5,6,7,3, POSITIVE); // LCD
#define DHT11_PIN 7																			// DHT
const int ldrPin = A0;																	// LDR
int moistPin = A1;																			// Soil Moisture
SoftwareSerial s(5, 6);																	// Node MCU Serial Communication

int tmp, lux, moist, hmd = 0;														// Initial variables for sensor

/* Serial lists
 *	UNO Serial 115200
 *	Node Serial 9600
 */

void setup() {
	// Pinsetup
	pinMode(ldrPin, INPUT);
	// DHT & Soil moisture sensore doesn't need pin setup
	
  // Own Serial
  Serial.begin(115200);

  // NodeMCU Serial
  s.begin(9600);

	// Boot msg
  Serial.print("Device Booting");
	lcd.print("Device Booting");
  for(int i=0; i<5; i++){
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

void Light(){
  lux = analogRead(ldrPin); // read the value from the sensor
  int ldrStatus= 0;
  Serial.println("Light: "+ String(lux));
  return;
}

void Temp(){
  int chk = DHT.read11(DHT11_PIN);
  tmp = DHT.temperature;
  Serial.println("Temp: "+String(tmp)+ String((char)223)+"C");
  hmd = DHT.humidity;
  Serial.println("Humid: "+String(hmd)+ "%");
  return;
}

void Moist(){
   moist= analogRead(moistPin);
//   moist = map(moist,550,0,0,100);
	 moist = (100 - ((moist/1023.00) *100);

   Serial.println("Moist: "+String(moist)+"%");
}

void transmitter(){
  String data = "h="+String(hmd)+"&m="+String(moist)+"&l="+String(lux)+"&t="+String(tmp)+"\n";
  
  int sz = data.length();
  for (int i = 0; i < sz; i++) {
    if (s.available() > 0) {
      s.write(data[i]);
      delay(10);
    }
    //  if(s.available()>0){
    //    s.write("c");
  }
  Serial.println(data);
  delay(500);
}

void Print(){
  lcd.clear();
//  lcd.print("Home Forestation!");
  lcd.setCursor(0,0);
	lcd.print("Hum: "+String(hmd)+"%; Soil="+String(moist)+"%");
	Serial.println("Hum: "+String(hmd)+"%; Soil="+String(moist)+"%");
	lcd.setCursor(0,1);
	lcd.print("lght="+String(lux)+"; tmp="+String(tmp)+String((char)223)+"C");
	Serial.println("lght="+String(lux)+"; tmp="+String(tmp)+String((char)223)+"C");

//  BT.println(sen+": "+String(var)+" "+unit);
  delay(2000);
}
