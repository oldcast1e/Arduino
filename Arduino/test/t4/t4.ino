int rst = A0;
void setup() {
  // put your setup code here, to run once:
    pinMode(rst,INPUT);
    Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int val= analogRead(rst);
  Serial.println(val);
  delay(100);

}
