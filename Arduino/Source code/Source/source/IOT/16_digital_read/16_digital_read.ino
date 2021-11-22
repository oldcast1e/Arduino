const int digitalPin = 4;
int digitalValue;

void setup() {
  Serial.begin(115200);

  pinMode(digitalPin, INPUT);
}

void loop() {
  digitalValue = digitalRead(digitalPin);
  Serial.println(digitalValue);
}