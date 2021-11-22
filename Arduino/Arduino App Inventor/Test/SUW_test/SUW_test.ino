#include <Servo.h>
Servo ms;

int E = 5;
int T = 3;

int st = LOW;

void sF(){
  st = (st==LOW)?HIGH:LOW;
  if(st==LOW){
      ms.write(75);
    }
    if(st==HIGH){
      ms.write(110);
  
  }
}
void setup(){
 pinMode(E,INPUT);
 pinMode(T,OUTPUT);

 Serial.begin(9600);
}

void loop(){

  digitalWrite(T,LOW);
  delayMicroseconds(2);

  digitalWrite(T,HIGH);
  delayMicroseconds(10);

  digitalWrite(T,LOW);

  unsigned long D = pulseIn(E,HIGH);
  long d = (D/2)/29.1;
  
  Serial.println(d);
  delay(500);
  
  if(d<70 && 80 < d){
    sF();
  }
  else sF();
  
}
