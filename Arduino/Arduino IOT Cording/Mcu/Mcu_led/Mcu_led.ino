const int Lesp = D0;
const int Lmcu  =D4;

const int Lon = LOW;
const int Loff = HIGH;

void setup(){

  pinMode(Lesp,OUTPUT);
  pinMode(Lmcu,OUTPUT);
}

void loop(){

  digitalWrite(Lesp,HIGH);
  digitalWrite(Lmcu,LOW);
  delay(1000);
  digitalWrite(Lesp,LOW);
  digitalWrite(Lmcu,HIGH);
  delay(1000);
  
}
