#include <SoftwareSerial.h>

SoftwareSerial btS = SoftwareSerial(9,10);
void setup(){
  Serial.begin(9600);
  btS.begin(9600);
}
void loop(){

  if(Serial.available()>0){
    btS.write(Serial.read());
  }
  if(btS.available()>0){
    Serial.write(btS.read());
  }
}
