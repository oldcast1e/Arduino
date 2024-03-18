const int b = 2;

void setup() {
 Serial.begin(115200);
 pinMode(b,INPUT);
}

void loop() {
  int d = digitalRead(b);
  Serial.println(d);
  delay(100);
}
