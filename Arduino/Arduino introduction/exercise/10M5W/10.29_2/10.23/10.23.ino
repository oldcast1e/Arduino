
void setup() {

Serial.begin(115200);
}
void loop() {
 
if(Serial.available()){
  char d = Serial.read();
  Serial.print(d);
  delay(10);
 }
}
