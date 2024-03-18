const int b = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(b,INPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  int n = digitalRead(b);
  Serial.println(n);
  delay(1000);
}
