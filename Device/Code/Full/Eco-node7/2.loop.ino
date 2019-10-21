
void loop()
{
  Blynk.run();
  String ADCData, station, postData;
  
  // Moist
   int mVal = analogRead(mPin);
  if(mVal > WaterValue && mVal < (WaterValue + intervals)) {
    mRes = "Very Wet";
  }
  else if(mVal > (WaterValue + intervals) && mVal < (AirValue - intervals)) {
    mRes = "Wet";
  }
  else if(mVal < AirValue && mVal > (AirValue - intervals)) {
    mRes = "Dry";
  }  
  
  // DHT
//  delay(dht.getMinimumSamplingPeriod()+500);

  humidity = dht.getHumidity();
  temperature = dht.getTemperature();
  


  // Light
  uint16_t lux = LightSensor.GetLightIntensity();
  postData = "";
//  postData = "?api="+srvr_api+"&light="+String(lux)+"&temperature="+String(temperature)+"&humidity="+String(humidity)+"&soil="+mRes+"&moisture="+mVal+"&remarks=";
//  postData = "?api="+srvr_api+"&light="+String(lux)+"&temperature="+String(temperature)+"&humidity="+String(humidity)+"&soil="+mRes+"&moisture="+mVal+"&remarks=";
  postData = "plant="+String(host)+"plants/1/&light="+String(lux)+"&temperature="+String(temperature)+"&humidity="+String(humidity)+"&soil="+mRes+"&moisture="+mVal+"&remarks=/";

  Serial.println("Request Check: "+postData);
  HTTPClient http;    //Declare object of class HTTPClient
  http.begin(String(host)+"datalogs/");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

  httpCode = http.POST(postData);   //Send the request
  payload = http.getString();    //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  
  htChecker();
  Serial.println(payload);    //Print request response payload
  http.end();  //Close connection




  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("\tHumd: ");
  Serial.print(humidity);

  
  Serial.print("\tLight: ");
  Serial.print(lux);
  
  Serial.print("\tMoist: ");
  Serial.print(mRes);
  Serial.println("");

  display.clearDisplay();
  
  display.setCursor(0,0);
//  display.println("00/00 00:00:00");
  display.println(payload);
  display.println("Srvr: "+ srvr);
  display.println("Lite: "+String(lux)+"    Lx");
  
  display.print("Temp: ");
  display.print(temperature);
  display.print(" ");
  display.print((char)247);
  display.println("C");

  display.print("Humd: ");
  
  display.print(humidity);
  display.println("  %");
  
  display.print("Soil: ");
  display.println(mRes);
  display.display();
  delay(1000);
  
}
