void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // LED ON
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);  // LED OFF
  delay(2000);
}