void serialflush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}   
