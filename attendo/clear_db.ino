//clear the template buffer
int clear_db(){
  Serial.println("Do you really like to clear whole database,enter your Pass key to confirm?");
  teacher_pass = readnumber();
  if(teacher_pass==PASS_KEY){Serial.println("Database Cleared");finger.emptyDatabase();}
  else Serial.println("Wrong Pass entered");
  return 0;
}

