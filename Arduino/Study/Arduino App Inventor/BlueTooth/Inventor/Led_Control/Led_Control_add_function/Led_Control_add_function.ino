#include <SoftwareSerial.h>

const int L[5]={2, 3, 4, 5, 6};

SoftwareSerial btS = SoftwareSerial(9, 10);

void DC() {

  for (int n = 0; n <= 4; n++) {
    digitalWrite(L[n], LOW);
  }
}

void setup() {

  for (int n = 0; n <= 4; n++) {
    pinMode(L[n], OUTPUT);
  }

  btS.begin(9600);
}

void loop() {

  if (btS.available() >0 ) {

    char u = btS.read();

    if (u == '1') {
      digitalWrite(L[0], HIGH);
      digitalWrite(L[1], LOW);
      digitalWrite(L[2], LOW);
      digitalWrite(L[3], LOW);
      digitalWrite(L[4], LOW);
    }

    else if (u == '2') {
      digitalWrite(L[0], LOW);
      digitalWrite(L[1], HIGH);
      digitalWrite(L[2], LOW);
      digitalWrite(L[3], LOW);
      digitalWrite(L[4], LOW);
    }

    else if (u == '3') {
      digitalWrite(L[0], LOW);
      digitalWrite(L[1], LOW);
      digitalWrite(L[2], HIGH);
      digitalWrite(L[3], LOW);
      digitalWrite(L[4], LOW);
    }

    else if (u == '4') {
      digitalWrite(L[0], LOW);
      digitalWrite(L[1], LOW);
      digitalWrite(L[2], LOW);
      digitalWrite(L[3], HIGH);
      digitalWrite(L[4], LOW);
    }

    else if (u == '5') {
      digitalWrite(L[0], LOW);
      digitalWrite(L[1], LOW);
      digitalWrite(L[2], LOW);
      digitalWrite(L[3], LOW);
      digitalWrite(L[4], HIGH);
    }

    else if (u == '6') {
      digitalWrite(L[0], HIGH);
      digitalWrite(L[1], HIGH);
      digitalWrite(L[2], HIGH);
      digitalWrite(L[3], HIGH);
      digitalWrite(L[4], HIGH);
    }//모든 LED 켜기
    else if (u == '7') {
      digitalWrite(L[0], LOW);
      digitalWrite(L[1], LOW);
      digitalWrite(L[2], LOW);
      digitalWrite(L[3], LOW);
      digitalWrite(L[4], LOW);
    }//모든 LED끄기
   else if(u=='8'){
      for(int n = 0;n<=4;n++){
        
     
         for(int x = 0;x<=4;x++){
          digitalWrite(L[x],LOW);
                   }
         digitalWrite(L[n],HIGH);
         delay(100);
      }
    }//웨이브

  else if(u=='9'){
      for(int n = 0;n<=4;n++){
        digitalWrite(L[n],HIGH);
                      
      }
      delay(100);
      for(int n = 0;n<=4;n++){
        digitalWrite(L[n],LOW);
               
      }
    }   


  }
}
