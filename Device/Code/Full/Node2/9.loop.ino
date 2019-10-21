void loop()
{
  DHT_INPUT();
  MOIST_INPUT();
  LIGHT_INPUT();
  PLANT_ALIVE();

  SERVER_POST();
  
  SENSOR_DISPLAY();

  
  delay(2000);
}
