const int L1 = 8;
const int L2 = 9;
const int L3 = 10;
const int L4 = 11;
const int L5 = 12;

void setup() {
  // put yofur setup code here, to run once:
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(L3,OUTPUT);
  pinMode(L4,OUTPUT);
  pinMode(L5,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

 while(1){

  digitalWrite(L1,HIGH);
  delay(100);
  digitalWrite(L1,LOW);

  digitalWrite(L2,HIGH);
  delay(100);
  digitalWrite(L2,LOW);

  digitalWrite(L3,HIGH);
  delay(100);
  digitalWrite(L3,LOW);

  digitalWrite(L4,HIGH);
  delay(100);
  digitalWrite(L4,LOW);

  digitalWrite(L5,HIGH);
  delay(100);
  digitalWrite(L5,LOW);

  
  
 }

}
