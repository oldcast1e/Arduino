#include <SoftwareSerial.h>
SoftwareSerial bts = SoftwareSerial(9,10);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bts.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(bts.available()>0){
    Serial.write(bts.read());
  }

  if(Serial.available()){
    bts.write(Serial.read());
  }

}
