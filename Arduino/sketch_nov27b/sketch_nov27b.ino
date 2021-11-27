void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello!");
  Serial1.begin(9600);
}
 
void loop() {
 
  // put your main code here, to run repeatedly:
  if (Serial1.available()) {
    Serial.write(Serial1.read());
  }
  // Serial –> Data –> BT
  if (Serial.available()) {
    Serial1.write(Serial.read());
 }
}
