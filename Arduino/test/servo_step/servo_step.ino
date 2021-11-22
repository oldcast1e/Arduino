#include<Servo.h>
Servo ms;

int angle = 90;
void setup() {
  // put your setup code here, to run once:
  ms.attach(7);
  ms.write(90);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    char u = Serial.read();
    if(u=='=' && angle < 170) angle += 10;
    else if(u =='-' && angle > 10) angle -= 10;
    
    ms.write(angle); 
    Serial.println(angle);

  }
}
