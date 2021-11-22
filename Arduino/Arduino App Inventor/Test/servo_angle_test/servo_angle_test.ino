#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial btS = SoftwareSerial(9,10);
Servo ms;

void setup(){

  ms.attach(6);
  btS.begin(9600);
  ms.write(90);
}

void loop(){

  if(btS.available()){

    int u = btS.read();

    if(u=='1'){
      ms.write(75);
    }
    if(u=='0'){
      ms.write(110);
    }
    if(u=='3'){
      ms.write(90);
    }
  }
  
}
