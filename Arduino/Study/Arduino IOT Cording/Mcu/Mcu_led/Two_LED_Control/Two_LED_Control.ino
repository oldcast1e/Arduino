const int LED[2]  = {16,2};

void setup() {
  // put your setup code here, to run once:
  pinMode(LED[0],OUTPUT);
  pinMode(LED[1],OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<2;i++){
    digitalWrite(LED[i],HIGH);
    delay(1000);
    digitalWrite(LED[i],LOW);
  }
  

}
