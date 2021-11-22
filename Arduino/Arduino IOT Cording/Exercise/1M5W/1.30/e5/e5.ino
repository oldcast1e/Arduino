const int L = 2;

void setup() {
  pinMode(L,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(L,digitalRead(L)^1);
  delay(1000);
  Serial.println(digitalRead(L)^1);
}
