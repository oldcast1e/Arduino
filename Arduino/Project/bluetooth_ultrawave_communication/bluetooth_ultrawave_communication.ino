#include <SoftwareSerial.h>
SoftwareSerial bts = SoftwareSerial(9,10);
const int tr = 3;
const int ec = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bts.begin(9600);

  pinMode(tr,OUTPUT);
  pinMode(ec,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(bts.available()>0){
    Serial.write(bts.read());
  }

  digitalWrite(tr,LOW);
  delayMicroseconds(2);
  digitalWrite(tr,HIGH);
  delayMicroseconds(10);
  digitalWrite(tr,LOW);
  long D = pulseIn(ec,HIGH);
  long d = (D/2)/29.1;

  delay(1000);
  
  bts.print(d);
  bts.println("cm");
  

  
  Serial.print(d);
  Serial.println( "cm");

}
/*
const int tr = 10;
const int ec = 11;

void setup() {

 pinMode(tr,OUTPUT);
 pinMode(ec,INPUT);

 Serial.begin(9600);
}

void loop() {

 


}
 */
