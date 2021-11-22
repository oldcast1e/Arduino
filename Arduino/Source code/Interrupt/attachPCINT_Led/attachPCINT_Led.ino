#include "PinChangeInterrupt.h"

const int LED = 13;
const int bt = 4;

int bts = true ;
bool btc = false;

void bf(){

  bts = (bts==HIGH?LOW:HIGH);
  btc = true;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  pinMode(bt,INPUT);
  Serial.begin(115200);
  attachPCINT(digitalPinToPCINT(bt),bf,RISING);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if(btc){
    digitalWrite(LED,bts);
    Serial.println(bts);
    btc = false;
  }

}
