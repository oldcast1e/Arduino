#include <SoftwareSerial.h>
SoftwareSerial bts = SoftwareSerial(1,0);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  bts.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
//  if(bts.available()>0){
//    Serial.write(bts.read());
//  }

  if(Serial.available()>0){
    bts.write(Serial.read());
  }
  if(bts.available()>0) Serial.write(bts.read());
  
}
