#include<Servo.h>
Servo ms;
void setup(){
    Serial.begin(9600);
    ms.attach(9);
    ms.write(0);
}
void loop(){
    if(Serial.available()>0){
        String angle = Serial.readStringUntil('\n');
        int angle_Num = angle.toInt();
        if(0<=angle_Num && angle_Num<=180) ms.write(angle_Num);
        delay(100);
    }
}