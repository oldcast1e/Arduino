const int Lesp = D0;
const int Lmcu  =D4;

void setup(){

  pinMode(Lesp,OUTPUT);
  pinMode(Lmcu,OUTPUT);
}

void loop(){

  for(int i=0;i<=1023;i++){
    analogWrite(Lmcu,i);
    delay(3);
  }
  for(int i=1023;i>=0;i--){
    analogWrite(Lmcu,i);
    delay(3);
  }
  
}
