// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK){  
    Serial.println("No Match Found");
    return -1;
  }
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  if(finger.confidence>CONFIDENCE_THRESHOLD){
     //put it into string
     id = finger.fingerID;
     Sense_Values+=String(id);
     Sense_Values+="x";
  }
  return finger.fingerID; 
}
