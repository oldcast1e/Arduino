const unsigned int L[7] = {4,5,6,7,8,9,10};
const int b = 2;

int LS = LOW;
bool LC = false; 

void bp(){

  LS =(LS==LOW)?HIGH:LOW;
  LC = true;
}

void setup() {

for(int x =0 ; x<7 ; x++){
pinMode(L[x],OUTPUT);
}

pinMode(b,INPUT);
attachInterrupt(digitalPinToInterrupt(b),bp,RISING);

}

void loop() {

  if(LC){
    LC = false;
    for(int t =0 ; t<7 ; t++){
    digitalWrite(L[t],LS);
}
  }
}
