void setup() 
{
  // Sensors initialize
  LightSensor.begin();  
  dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 17

  // GUI Initialized
  Serial.begin(115200);
  
  display.begin();
  display.setContrast(50);
  display.setRotation(2);
  

  // Device boot
  Serial.println("Device Booting...");
  load_logo();
  
  display.clearDisplay();   // clears the screen and buffer
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);


  // WiFi Connection
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    display.print(".");
    loading_animation();
  }
  delay(500);
  
  //If connection successful show IP address in serial monitor
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP


  display.clearDisplay();   // clears the screen and buffer
  display.setCursor(0,0);
  display.println("Connected to: ");
  display.println("   "+String(ssid));
  display.println("IP Address: ");
  display.print("   ");
  display.println(WiFi.localIP());
  display.display();
  delay(2000);
  
}
