const int L = 10;

void setup() {
  // put your setup code here, to run once:
pinMode(L,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
for(int x=0;x<=255;x++){

  analogWrite(L,x);
  delay(10);
}

}
