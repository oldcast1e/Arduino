void setup() {
  Serial.begin(115200);

  if(Serial.available()>0){

    char u = Serial.read();
    if(20<=u<=30){
      Serial.println("1");
    }
    else
      Serial.println("2");
  }
  

}

void loop() {
  

}
