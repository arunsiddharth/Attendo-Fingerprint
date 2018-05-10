String readstring(){
  String num = "5";
  while (num[0]=='5') {
    while (!Serial.available());
    num = Serial.readString();
  }
  return num;
}
