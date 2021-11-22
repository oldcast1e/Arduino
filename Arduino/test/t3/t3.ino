#include<stdlib.h>
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial btS = SoftwareSerial(9,10);
Servo ms;

void setup(){

  ms.attach(7);
  btS.begin(9600);
}

void loop(){

  if(btS.available()){

    int u = atoi(btS.read());

    if(0<= u && u<=180){
      ms.write(u);
      delay(15);
    }
  }
  
}
