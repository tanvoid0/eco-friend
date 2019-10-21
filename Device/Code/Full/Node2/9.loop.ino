void loop()
{
  DHT_INPUT();
  MOIST_INPUT();
  LIGHT_INPUT();

  SERVER_POST();
  
  SENSOR_DISPLAY();

  
  delay(2000);
}
