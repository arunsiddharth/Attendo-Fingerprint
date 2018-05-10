void fast_esp(){
  ESP8266.begin(9600);//default baudrate for ESP
  ESP8266.listen();//not needed unless using other software serial instances
  delay(2500);//delay before kicking things off
  //Here's where the SSID and PW are set
  ESP8266.print("AT+CWJAP=\"");// set the SSID AT+CWJAP="SSID","PW"
  ESP8266.print(SSID_ESP);//from constant 
  ESP8266.print("\",\"");
  ESP8266.print(SSID_KEY);//form constant
  ESP8266.print("\"\r\n");
  
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),10000,0))//go look for keyword "OK"
    Serial.println("ESP SSID SET OK");
  else
    Serial.println("ESP SSID SET FAILED");   
  serial_dump_ESP();
   ESP8266.print("AT+CIPMUX=");// set the CIPMUX
   ESP8266.print(CIPMUX);//from constant
   ESP8266.print("\r\n");
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),15000,0))//go look for keyword "OK" or "no change
    Serial.println("ESP CIPMUX SET");
  else
    Serial.println("ESP CIPMUX SET FAILED"); 
  serial_dump_ESP();
}//setup ESP
