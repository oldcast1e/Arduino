const int analogPin = A0;
int analogValue;

void setup() {
  Serial.begin(115200);
}

void loop() {
  analogValue = analogRead(analogPin);
  Serial.println(analogValue);
}