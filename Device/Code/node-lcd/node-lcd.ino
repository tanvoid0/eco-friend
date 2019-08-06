
 
// Nokia 5110 LCD module connections (CLK, DIN, D/C, CS, RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(D7, D6, D5, D4, D3);
 
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

void setup()   {
  Serial.begin(9600);
 
  display.begin();
  // init done
 
  display.setContrast(50);
// 
  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();   // clears the screen and buffer
 
  display.setTextSize(1);
  display.setTextColor(BLACK);
}
 
 
void loop() {
   // text display tests
  display.clearDisplay();
  
  display.setCursor(0,0);
  display.println("Light : 15 Lux");
  
  display.print("Temp: ");
  display.print("31.2");
  display.print((char)247);
  display.println("C");

  display.println("Hum  : 30%");
  display.println("Moist: 30%");
  display.display();
  delay(2000);
  

}
 
 
void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
 
  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    //if ((i > 0) && (i % 14 == 0))
      //display.println();
  }    
  display.display();
}
 
 
// end of code.
