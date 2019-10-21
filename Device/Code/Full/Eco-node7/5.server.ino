

void htChecker(){
 if(httpCode == 200){
    srvr = "Online";
  }
  else {
    payload = "HTTP "+httpCode;
    srvr = srvr_stat[0];
    if(httpCode == 400){
      srvr = "Bad Req.";
    }
    else if(httpCode == 401){
      srvr = "Unauth.";
    }
    else if(httpCode == 403){
      srvr = "Forbid.";
    }
    else if(httpCode == 404){
      srvr = "Not Found";
    }
  }
  return;
}
