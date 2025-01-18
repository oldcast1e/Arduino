#include<Servo.h>
Servo ms;
void setup(){
    Serial.begin(9600);
    ms.attach(9);
    ms.write(90);
}
void loop(){
    if(Serial.available()>0){
        char u = Serial.read();
        if(u!= '\n'){
            if(u == '1') ms.write(0);
            else if(u == '2') ms.write(30);
            else if(u == '3') ms.write(60);
            else if(u == '4') ms.write(90);
            else if(u == '5') ms.write(120);
            else if(u == '6') ms.write(180);

            delay(100);
        }
    }
}