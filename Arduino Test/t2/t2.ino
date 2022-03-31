//#include<Servo.h>
//
//Servo ms;

const int bt = 2;
int on_off = 0;
boolean sts = 0;

void setup(){
    Serial.begin(9600);
    pinMode(bt,INPUT);
//    ms.attach(6);
//    ms.write(0);
}
void loop(){
  int val = digitalRead(bt);
  if(bt == 1){
    on_off = 1;
    sts = (sts == 1)?0:1;
    delay(100);
  }
  
  
  Serial.println(on_off);
  delay(100);
  
  
  
    
}
