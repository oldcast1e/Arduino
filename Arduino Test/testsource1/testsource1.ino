void setup() {
  // pinMode(13, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  Serial.print("#4P800T3000\r\n");
  delay(1000);
  Serial.print("#4P1800T3000\r\n");
  delay(1000);

}
