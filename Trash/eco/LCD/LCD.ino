#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2,1,0,4,5,6,7,3, POSITIVE);
//LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Wire.begin(8); 
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Home Forestation!");
}
void loop()
{
}

