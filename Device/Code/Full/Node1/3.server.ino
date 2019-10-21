void SERVER_POST{
  String station, postData;
  
  postData = "?api="+srvr_api+"&light="+String(lux)+"&temperature="+String(temperature)+"&humidity="+String(humidity)+"&soil="+mRes+"&moisture="+mVal+"&remarks=";
  Serial.println("Request Check: "+postData);

  // A complete request
  HTTPClient http;                                                        //Declare object of class HTTPClient
  http.begin(host+postData);                                              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  httpCode = http.GET();                                                  //Send the request
  payload = http.getString();                                             //Get the response payload

  Serial.println(httpCode);                                                //Print HTTP return code  
  srvr = htChecker();
  
  Serial.println(payload);    //Print request response payload
  http.end();  //Close connection
  // Request Ends
}


String htChecker(){
  switch (httpCode) {
  String output = "";
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

String responseChecker(){
  switch (httpCode) {
  String output = "";
  case 200:
    output = "200 OK:\nThe request has succeeded.";
    break;

  case 300:
    output = "300 Multiple Choices:\nThe requested resource has different choices and cannot be resolved into one.";
    break;
  case 301:
    output = "301 Moved Permanently:\nThe requested resource has been assigned a new permanent URI and any future references to this resource should use one of the returned URIs.";
    break;
  case 302:
    output = "302 Found:\nThe requested resource resides temporarily under a different URI.";
    break;
  case 304:
    output = "304 Not  Modified:";
    break;

  case 400:
    output = "400 Bad Request:\nHTTP request that was sent to the server has invalid syntax.";
    break;
  case 401:
    output = "401 Unautorized:\nThe user trying to access the resource has not been authenticated or has not been authenticated correctly.";
    break;
  case 403:
    output = "403 Forbiden:\nThe user made a valid request but the server is refusing to serve the request, due to a lack of permission to access the requested resource.";
    break;
  case 404:
    output = "404 Not Found:\nThe user is able to communicate with the server but it is unable to locate the requested file or resource.";
    break;

  case 500:
    output = "500 Internal Server Error:\nThe server cannot process the request for an unknown reason.";
    break;
  case 502:
    output = "502 Bad Gateway:\nThe server cannot process the request for an unknown reason. ";
    break;
  case 503:
    output = "503 Service Unavailable:\nThe server is overloaded or under maintenance.";
    break;
  case 504:
    output = "504 Gateway Timeout:\nThe server is a gateway or proxy server, and it is not receiving a response from the backend servers within the allowed time period.";
    break;
  case 550:
    output = "550 Permission Denied:\nThe server is stating the account you have currently logged in as does not have permission to perform the action you are attempting. You may be trying to upload to the wrong directory or trying to delete a file.";
    break;
  default:
    output = "Unknown Error";
    break;
  } 
  return output;

}
