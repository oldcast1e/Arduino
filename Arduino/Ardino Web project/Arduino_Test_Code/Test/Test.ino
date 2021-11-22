#include<Servo.h>
Servo ms;

const int tr = 9;
const int ec = 10;

int bt = LOW;

void setup() {

  pinMode(tr,OUTPUT);
  pinMode(ec,INPUT);
  ms.attach(3);
  ms.write(0);
 
  Serial.begin(9600);
}

void loop() {

   digitalWrite(tr,LOW);
   delayMicroseconds(2);
   digitalWrite(tr,HIGH);
   delayMicroseconds(10);
   digitalWrite(tr,LOW);
   
   long D = pulseIn(ec,HIGH);
   long d = (D/2)/29.1;

    delay(100);
    
    if(10 <= d && d<= 70){
      
      bt  = (bt == LOW?HIGH:LOW);
      if(bt == LOW) ms.write(115);
      else if(bt == HIGH) ms.write(72);

      Serial.println(d);
      delay(1000);
 }
// 
// 
//
// delay(100);



}
