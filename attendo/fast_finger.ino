void fast_finger(){  
  finger.begin(57600);
  if (finger.verifyPassword()) 
  {
    Serial.println("Fingerprint sensor ON!");
  } 
  else 
  {
    Serial.println("Fingerprint sensor OFF!");
    while (1) { delay(1); }
  } 
 }
