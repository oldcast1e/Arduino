const int Larr[5] = {8,9,10,11,12};

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<5;i++){
    pinMode(Larr[i],OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<5;i++){
    digitalWrite(Larr[i],HIGH);
    delay(1000);
    digitalWrite(Larr[i],LOW);
  }
}
