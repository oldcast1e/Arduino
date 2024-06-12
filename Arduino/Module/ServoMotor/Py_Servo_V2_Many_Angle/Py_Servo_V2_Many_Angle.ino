#include<Servo.h>
Servo ms;
void setup(){
    Serial.begin(9600);
    ms.attach(9);
    ms.write(0);
}
void loop(){
    if(Serial.available()>0){
        char u = Serial.read();
        if(u!= '\n'){
            if(u == 'a') ms.write(0);
            else if(u == 'b') ms.write(15);
            else if(u == 'c') ms.write(30);
            else if(u == 'd') ms.write(45);
            else if(u == 'e') ms.write(60);
            else if(u == 'f') ms.write(75);
            else if(u == 'g') ms.write(90);
            else if(u == 'h') ms.write(105);
            else if(u == 'i') ms.write(120);
            else if(u == 'j') ms.write(135);
            else if(u == 'k') ms.write(150);
            else if(u == 'l') ms.write(175);
            else if(u == 'm') ms.write(180);

            delay(100);
        }
    }
}