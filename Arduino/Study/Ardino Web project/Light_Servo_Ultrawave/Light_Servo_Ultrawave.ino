#include <SoftwareSerial.h>
#include <Servo.h>

   
#include <SoftwareSerial.h>
SoftwareSerial bts = SoftwareSerial(5,3);

const int light = A0;// 조도 센
int light_status = false,key = 0;

const int tr = 10;
const int ec = 11;
int tot_person = 0;

Servo ms;

void setup(){

  ms.attach(6);

  pinMode(tr,OUTPUT);
  pinMode(ec,INPUT);
 
  Serial.begin(9600);
  bts.begin(9600);
  
  pinMode(light, INPUT);
}

int Function_Ultra(int tr,int ec){

  int person_num = 0;
  digitalWrite(tr,LOW);
  delayMicroseconds(2);
  
  digitalWrite(tr,HIGH);
  
  delayMicroseconds(10);
  digitalWrite(tr,LOW);
  long uncalculation = pulseIn(ec,HIGH);
  long result = (uncalculation/2)/29.1;

  delay(1000);

  if(result < 65){
     return 1;
//    delay(3000);
  }
  else return 0;
//  Serial.print(result);
//  Serial.println( "cm");
//
//  bts.print(result);
//  bts.println(" cm");

//  delay(1000);
  
}

int Function_Light(int val){

  if(val > 230){ light_status  = false;key == 1 ? 0: 1;}
  else {light_status  = true;key == 1 ? 0: 1;}

  if(light_status == 1 && key == 0){ Serial.println("Light Status is ON"); key = 1 ; return 1;}
  else if(light_status == 0 && key == 1){Serial.println("Light Status is OFF");key = 0; return 0;}
  else return 3;
  delay(100);

  
}


void loop(){

//  int lightV = analogRead(light);//조도 센서 값 저
  int val = analogRead(light)/4;
  
  int light_st = Function_Light(val);//조도센서 함수 리턴값
  //1일때 on | 0일때 off
//  if(light_st == 1 || light_st == 0 ){
//    Serial.println(light_st);    
//  }

//  int person_num = Function_Ultra(tr,ec);
//  if(person_num == 1){
//    tot_person ++;
//    Serial.print("Total Person : ");
//    Serial.println(tot_person);
//  }

  

  

  
  
  
   
  
  
}
