#include<SoftwareSerial.h>
SoftwareSerial bts  = SoftwareSerial(9,10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bts.begin(9600);

  pinMode(7,OUTPUT);
  digitalWrite(7,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(bts.available()>0){
    char u =  bts.read();
    if(u=='0') digitalWrite(7,LOW);
    else if(u=='1') digitalWrite(7,HIGH);
    
  }
  if(Serial.available()>0){
    char u =  Serial.read();
    if(u=='0') digitalWrite(7,LOW);
    else if(u=='1')digitalWrite(7,HIGH);
    
  }

}
