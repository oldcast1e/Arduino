# include "PinChangeInterrupt.h"

const int b = 4;
const int L = 13;

int ls = LOW;
bool lc = false;

void bp(){

  ls =(ls ==LOW)?HIGH:LOW;
  lc = true;
}
void setup() {

 pinMode(L,OUTPUT);
 pinMode(b,INPUT);

 attachPCINT(digitalPinToPCINT(b),bp,RISING);

}

void loop() {

  if(lc){
    lc = false;
    digitalWrite(L,ls);
  }
 
}
