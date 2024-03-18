#include <SoftwareSerial.h>

SoftwareSerial btS = SoftwareSerial(9,10); //9는 TX 10은 RX
const int L[5] = {2,3,4,5,6};

void setup(){

  btS.begin(9600);

  for(int n=0;n<=4;n++){
    pinMode(L[n],OUTPUT);
  }
}

void loop(){

  if(btS.available()>0){

    char u = btS.read();

    if(u=='1'){
      digitalWrite(L[0],HIGH);
      digitalWrite(L[1],LOW);
      digitalWrite(L[2],LOW);
      digitalWrite(L[3],LOW);
      digitalWrite(L[4],LOW);
      
    }

    if(u=='2'){
      digitalWrite(L[0],LOW);
      digitalWrite(L[1],HIGH);
      digitalWrite(L[2],LOW);
      digitalWrite(L[3],LOW);
      digitalWrite(L[4],LOW);
      
    }

    if(u=='3'){
      digitalWrite(L[0],LOW);
      digitalWrite(L[1],LOW);
      digitalWrite(L[2],HIGH);
      digitalWrite(L[3],LOW);
      digitalWrite(L[4],LOW);
      
    }

    if(u=='4'){
      digitalWrite(L[0],LOW);
      digitalWrite(L[1],LOW);
      digitalWrite(L[2],LOW);
      digitalWrite(L[3],HIGH);
      digitalWrite(L[4],LOW);
      
    }

    if(u=='5'){
      digitalWrite(L[0],LOW);
      digitalWrite(L[1],LOW);
      digitalWrite(L[2],LOW);
      digitalWrite(L[3],LOW);
      digitalWrite(L[4],HIGH);
      
    }
    
  }
}
