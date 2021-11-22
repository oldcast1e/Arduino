const int L = 13;

void setup() {

  pinMode(L,OUTPUT);

}

void loop() {

 for(int x = 0; x<=1;x++){
  digitalWrite(L,x);
  delay(1000);
 }

}
