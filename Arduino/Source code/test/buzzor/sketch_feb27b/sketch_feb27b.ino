const int buz = 10;

void setup() {
  pinMode(buz,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(buz,HIGH);
  delay(1000);
  digitalWrite(buz,LOW);
  delay(1000);

}
