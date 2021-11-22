void setup() {

 Serial.begin(115200);


}

void loop() {

  if(Serial.available()){
    char u = Serial.read();

    Serial.print(u);
  }
}
