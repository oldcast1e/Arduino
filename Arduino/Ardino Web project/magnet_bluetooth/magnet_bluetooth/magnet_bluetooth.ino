#include <SoftwareSerial.h>
#define MAGNET 2

SoftwareSerial bts = SoftwareSerial(8,9);
int mg_sts = LOW;
bool mg_cst = false; 

void door_status(){
  mg_sts =(mg_sts==LOW)?HIGH:LOW;
  delay(1500);
  mg_cst = true;

}
void setup() {
  // put your setup code here, to run once:
  pinMode(MAGNET,INPUT);
  Serial.begin(9600);
  bts.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(MAGNET),door_status,RISING);

}

void loop() {
  // put your main code here, to run repeatedly:
//  if(bts.available()>0){
//    Serial.write(bts.read());
//  }
//
//  if(Serial.available()){
//    bts.write(Serial.read());
//  
  if(mg_cst){
    mg_cst = false;
    if(mg_sts== LOW){
      Serial.println("Door Open");
      bts.println("Door Open");
      delay(1000);
    }
    else if (mg_sts == HIGH){
      Serial.println("Door Close");
      bts.println("Door Close");
      delay(1000);
    }  
  }
  

}
