#include <SoftwareSerial.h>

SoftwareSerial btS = SoftwareSerial(9,10);
const int B = 2;

void setup(){
  pinMode(B,INPUT);
  btS.begin(9600);
}

void loop(){

  int ss = digitalRead(B);

  if(ss==1){
    btS.println("SW ON");
  }

  if(ss==0){
    btS.println("SW OFF");
  }
  delay(300);
  
}
