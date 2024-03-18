int value = 0;

void setup(){
  
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (value<=255){
    value += 5;
    if (value > 255){
      value = 255;
    }
  }
  if(value<255){
     Serial.println(value);
}
}
