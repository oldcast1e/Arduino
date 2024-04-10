int Lazer = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(Lazer,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Lazer,HIGH);
  delay(500);
  digitalWrite(Lazer,LOW);
  delay(500);
}
