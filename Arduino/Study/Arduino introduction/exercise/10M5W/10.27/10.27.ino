#include <Servo.h>

const int m = 9;
const int b = 10;

Servo s;

void setup() {

pinMode(b,INPUT);
s.attach(m);
s.write(0);

}
void loop() {

int k = digitalRead(b);
if(k == 1)
 s.write(150);

  else 
    s.write(30);
  
}
  
