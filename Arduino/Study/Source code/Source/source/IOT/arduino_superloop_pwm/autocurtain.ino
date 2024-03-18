#include <Servo.h>

Servo myservo;

int potpin = A0;
int val;

long autocurtain_previousMillis = 0;
long autocurtain_interval = 15;  

void autocurtain_setup() {
  myservo.attach(9);
}

void autocurtain_loop() {
  unsigned long currentMillis = millis();
 
  if(currentMillis - autocurtain_previousMillis >= autocurtain_interval) {
    autocurtain_previousMillis = currentMillis;
    
    val = analogRead(potpin);
    val = map(val, 0, 1023, 0, 180);
    myservo.write(val);
  }
}  
