#include<Servo.h>
Servo ms;
int LED = 13;
void setup(){

  // digitalWrite(LED,OUPUT);
  pinMode(LED,OUTPUT);
    Serial.begin(9600);
    ms.attach(9);
    ms.write(0);
}
void loop(){
    ms.write(90); digitalWrite(LED,HIGH);
    delay(5000);
    ms.write(0); digitalWrite(LED,LOW);
    delay(5000);

}