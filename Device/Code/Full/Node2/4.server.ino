// Set Static ip: netsh interface ip set address name="Ethernet" static 192.168.0.111 255.255.255.0 192.168.0.1
void SERVER_POST(){
  GET_REQUEST();
 
}


void WIFI_SETUP(){

  ssid = "Fokinnira dure thak";
  password = "murikha_sala";
//  host = "http://192.168.0.106:8000";
  
  srvr_api = "7^q$dwk0-@vf+8yi(jk2&6*qozex&h-^6#$yvw#ba7#_6w6@5c";
  
  
  
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
  Serial.print("Connected to "+String(ssid)+"\nIP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  display.clearDisplay();   // clears the screen and buffer
  display.println("Connected to: ");
  display.println("   "+String(ssid));
  display.println("IP Address: ");
  display.print("   ");
  display.println(WiFi.localIP());
  display.display();
}

void GET_REQUEST(){
  HTTPClient http;
  Serial.println("Host: "+String(host));
  String links = String(host)+String(url);
  Serial.println("Links: "+String(links));
  http.begin(links);
  httpCode = http.GET();
  payload =http.getString();
  Serial.println("GET REQUEST PAYLOAD: "+String(payload));
  Serial.println("GET REQUEST RESPONSE: "+String(htChecker()));
  http.end();
}

void POST_REQUEST(){
   String station, postData;
  
  
  Serial.println("Request Check: "+postData);
  Serial.println("Host: "+host);
  
  
  HTTPClient http; 
  host = "http://djangpi.herokuapp.com/api";
  String address = host + url; 
  
  postData = "light="+String(lux)+"&temperature="+String(temperature)+"&humidity="+String(humidity)+"&soil="+mRes+"&moisture="+mVal+"&remarks=null/";
  http.begin(address); 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(postData); 
  Serial.println(httpCode); //Print HTTP return code 
  String payload = http.getString(); 
  Serial.println(payload); //Print request response payload 
  http.end(); //Close connection Serial.println(); 
  Serial.println("closing connection"); 
}
String htChecker(){
  String output = "";
  switch (httpCode) {
    case -1:
      output = "-1 Bullshit error";
      break;
    case 200:
      output = "200 OK";
      break;
  
    case 300:
      output = "300 Multiple Choices";
      break;
    case 301:
      output = "301 Moved Permanently";
      break;
    case 302:
      output = "302 Found";
      break;
    case 304:
      output = "304 Not  Modified:";
      break;
  
    case 400:
      output = "400 Bad Request";
      break;
    case 401:
      output = "401 Unautorized";
      break;
    case 403:
      output = "403 Forbiden";
      break;
    case 404:
      output = "404 Not Found";
      break;
  
    case 500:
      output = "500 Internal Server Error";
      break;
    case 502:
      output = "502 Bad Gateway";
      break;
    case 503:
      output = "503 Service Unavailable";
      break;
    case 504:
      output = "504 Gateway Timeout";
      break;
    case 550:
      output = "550 Permission Denied";
      break;
    default:
      output = "Unknown Error";
      break;
  } 
  return output;

}
