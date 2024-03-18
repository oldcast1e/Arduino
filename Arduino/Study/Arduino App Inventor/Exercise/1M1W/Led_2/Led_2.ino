const int L = 10;

void setup() {
  // put your setup code here, to run once:
pinMode(L,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(L,HIGH);
delay(1000);

digitalWrite(L,LOW);
delay(1000);
}
