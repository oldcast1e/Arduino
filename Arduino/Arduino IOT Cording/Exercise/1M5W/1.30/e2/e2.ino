const int L1 = 2;
const int L2 = 3;

void setup(){
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
}

void loop(){
  digitalWrite(L2,HIGH);
  delay(1000);
  digitalWrite(L2,LOW);
  for(int n = 0;n<=255;n+=5){
    analogWrite(L1,n);
    delay(30);
  }
  for(int n = 255;n>=0;n-=5){
    analogWrite(L1,n);
    delay(30);
  }
}
