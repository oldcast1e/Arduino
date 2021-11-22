const int L= 12;
const int B = 2;

int LS = LOW;
bool LSC = false;

void BP(){

  LSC = true;
  LS = (LS==LOW)?HIGH:LOW;
}

void setup (){

  pinMode(L,OUTPUT);
  pinMode(B,INPUT);

  attachInterrupt(digitalPinToInterrupt(B),BP,RISING);
}

void loop(){

  if(LSC){

    LSC = false;
    digitalWrite(L,LS);
  }
}
