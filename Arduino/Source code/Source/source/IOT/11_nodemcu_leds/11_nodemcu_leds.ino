const int ledESP12 = D0; //16도 가능
const int ledNodeMCU = D4; //2도 가능
const int LED_ON = LOW;
const int LED_OFF = HIGH;

void setup() {
  pinMode(ledESP12, OUTPUT);
  pinMode(ledNodeMCU, OUTPUT);
}

void loop() {
  digitalWrite(ledESP12, LED_ON);
  digitalWrite(ledNodeMCU, LED_ON);
  delay(1000);
  digitalWrite(ledESP12, LED_OFF);
  digitalWrite(ledNodeMCU, LED_OFF);
  delay(1000);
}