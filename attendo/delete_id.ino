//delte id stord in r307 but not in cloud so delete
void delete_id(){
  Serial.println("Stored to device but not on cloud so deleting, please check your connection before enrolling again!");
  id = get_id();
  Serial.print("Deleting ID #");
  Serial.println(id);
  deleteFingerprint(id);
}
