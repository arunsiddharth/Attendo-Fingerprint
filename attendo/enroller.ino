uint8_t enroller(){
  Serial.println("Ready to enroll a fingerprint!");
  id = (uint8_t)get_id()+1;
  if(id==MAX_SPACE){
    Serial.println("Sensor memory is FULL");
    return 0;
  }
  
  fast_finger();
  Serial.println("Please type in your institue ID you want to save this finger as : ");
  sid = readstring();
  Serial.print("Enrolling ID #");
  Serial.print(id);
  Serial.print(" with student id : ");
  Serial.println(sid);
  while(!getFingerprintEnroll());
}

