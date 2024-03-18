const int L = 10;
const int b = 2;

int LS = LOW;
bool LC = false; 

void bp(){

  LS =(LS==LOW)?HIGH:LOW;
  LC = true;
}
void setup() {

pinMode(L,OUTPUT);
pinMode(b,INPUT);

attachInterrupt(digitalPinToInterrupt(b),bp,RISING);

}

void loop() {

  if(LC){
    LC = false;
    digitalWrite(L,LS);
  }

}
