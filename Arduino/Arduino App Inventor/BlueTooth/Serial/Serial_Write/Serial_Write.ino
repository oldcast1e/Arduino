#include <SoftwareSerial.h>

SoftwareSerial btS = SoftwareSerial(0,1);

void setup(){

  Serial.begin(9600);
  btS.begin(9600);
}

void loop(){

  if(btS.available()>0){
    Serial.write(btS.read());
  }

  if(Serial.available()>0){
    btS.write(Serial.read());
  }
}
