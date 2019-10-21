void LcdClear(void)
{
  for (int index = 0; index < LCD_X * LCD_Y / 8; index++)
  {
    LcdWrite(LCD_D, 0x00);
  }
  
  display.setRotation(2);
}

void LcdInitialise(void)
{
  pinMode(PIN_SCE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
  LcdWrite(LCD_C, 0x21 );  // LCD Extended Commands.
  LcdWrite(LCD_C, 0xB1 );  // Set LCD Vop (Contrast). 
  LcdWrite(LCD_C, 0x04 );  // Set Temp coefficent. //0x04
  LcdWrite(LCD_C, 0x14 );  // LCD bias mode 1:48. //0x13
  LcdWrite(LCD_C, 0x0C );  // LCD in normal mode.
  LcdWrite(LCD_C, 0x20 );
  LcdWrite(LCD_C, 0x0C );
}

void gotoXY(int x, int y)
{
  LcdWrite( 0, 0x80 | x);  // Column.
  LcdWrite( 0, 0x40 | y);  // Row. 

}
void LcdWrite(byte dc, byte data)
{
  digitalWrite(PIN_DC, dc);
  digitalWrite(PIN_SCE, LOW);
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data);
  digitalWrite(PIN_SCE, HIGH);
}

void LcdBitmap(char my_array[]){
  for (int index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++){
    display.setRotation(2);
    LcdWrite(LCD_D, my_array[index]);
  }
}

void load_logo(){
  LcdInitialise();
  LcdClear();
  gotoXY(0,0);
  LcdBitmap(bmp1);
  delay(5000);
}

void loading_animation()
{
  //loading screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);          //set text color, only BLACK or WHITE is to be used
  display.setCursor(8,8);
  display.print("Eco Friend");
  display.setCursor(0,20);
  display.println("Connecting");
  display.print("to Server...");
  display.write(3);
  display.drawRect(0,40,84,5,BLACK);    //draw a rectangle
  display.display();
  for (int l=0;l<85;l++)
  {
    display.fillRect(0,40,l,5,BLACK);   //color the rectangle
    delay(40);
    display.display();
  }
  display.clearDisplay();
}
