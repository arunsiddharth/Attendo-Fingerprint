/***CONNECT TO SERVER***/
boolean connect_attendo(){

  Serial.println("CONNECTING");
  ESP8266.print("AT+CIPSTART=0,\"TCP\",\"pbat.000webhostapp.com\",80\r\n");

  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),10000,0)){
    serial_dump_ESP();//get rid of whatever else is coming
  
    Serial.println("CONNECTED");//Connected to site
  
    //NOW WE SEND URL OF PAGE ON THAT SITE
    ESP8266.print("AT+CIPSEND=0,");//send AT+CIPSEND=0, size of payload
    ESP8266.print(payload_size);//the payload size
  
    serial_dump_ESP();//everything is echoed back, so get rid of it
    ESP8266.print("\r\n");//Connect to this WEBSITE BY HITTING /r/n

    //LOOK FOR '>'
      if(read_until_ESP(keyword_carrot,sizeof(keyword_carrot),5000,0)){
        Serial.println("READY TO SEND");
        Serial.println("Connected To PBAT");
      for(int i=0; i<payload_size; i++)//print the payload(page url) to the ESP
        ESP8266.print(payload[i]);

      //SEND it to SITE
      if(read_until_ESP(keyword_sendok,sizeof(keyword_sendok),5000,0)){
        Serial.println("SENT");
        
        return 1;
      }// got the SEND OK
      else// SEND OK
        Serial.println("FAILED TO SEND");
        return 0;
    }//got the back carrot >
  
    else
      Serial.println("FAILED TO GET >");
      return 0;
    }//First OK

  //NOT able to connect to main SITE
  else{
    Serial.println("FAILED TO CONNECT");
    setup_ESP();//setup the module and attempt to repair itself - connect to SSID, set the CIPMUX, etc...
    return 0;
  }
  
}// VOID CONNECT FUNCTION
