#include<Servo.h>
Servo ms;
void setup() {
  // put your setup code here, to run once:
  ms.attach(7);
  ms.write(0);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    char u = Serial.read();
    if(u=='0') ms.write(0);  
    else if(u =='1') ms.write(30);  
    else if(u =='2') ms.write(60);  
    else if(u =='3') ms.write(90);  
    else if(u =='4') ms.write(120);  
    else if(u =='5') ms.write(150);  
    else if(u =='6') ms.write(180);  

  }
}
