void LCD_SETUP(){
  display.begin();
  display.setContrast(50);
  display.setRotation(2);
  Serial.println("Device Booting...");
  load_logo();
  display.clearDisplay();   // clears the screen and buffer
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
}
void SENSOR_DISPLAY(){
  
  String output = 
//        String("Srvr: ")+String(httpCode == 200? "Online\n" : "Offline\n")+
        String("Srvr: ")+String(httpCode)+
        String("\nLite: ")+String(lux)+String(" Lx\n")+
        String("Temp: ")+String(temperature)+String("C\n")+
        String("Humd: ")+String(humidity)+String(" %\n")+
        String("Soil: ")+String(mRes)+String("\n")+
        String("Mois: ")+String(mVal);
  Serial.println(output);
    
  display.clearDisplay();
  display.setCursor(0,0);
  display.print(output);
  display.display();
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
