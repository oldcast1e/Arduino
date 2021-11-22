#include <PinChangeInterrupt.h>

const int tp = 11;
const int ep = 12;


unsigned long ecd = 0;

void ecI (void){

  static unsigned long e_b =0;
  static unsigned long e_e =0;

  unsigned int eps = digitalRead(ep);

  if(eps == HIGH){
    e_b = micros();
  }

  else{
    e_e = micros();
    ecd = e_e - e_b;
  }
}
void setup() {
 
pinMode(tp,OUTPUT);
pinMode(ep,INPUT);

attachPCINT(digitalPinToPCINT(ep),ecI,CHANGE);

Serial.begin(115200);
}

void loop() {

  if(ecd ==0){
    digitalWrite(tp,LOW);
    delayMicroseconds(2);
     digitalWrite(tp,HIGH);
    delayMicroseconds(10);
    digitalWrite(tp,LOW);
    
  } else{
    unsigned long d = ecd/58;
    Serial.print(d);
    Serial.println(" cm");

    ecd = 0;
  }

}
