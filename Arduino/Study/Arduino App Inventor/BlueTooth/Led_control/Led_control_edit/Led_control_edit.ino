#include <SoftwareSerial.h>

const int L[5] = {2,3,4,5,6};

SoftwareSerial btS = SoftwareSerial(9,10);

void DC(){

  for(int x=0;x<=4;x++){
    digitalWrite(L[x],LOW);
  }
}


void setup(){

  for(int x=0;x<=4;x++){
    pinMode(L[x],OUTPUT);
  }

  Serial.begin(9600);
  btS.begin(9600);

  DC();
}

void loop(){

  if(btS.available()>0){

   
    for(int n=1;n<=5;n++){

     char u = btS.read();      
    if(u == 'n'){

      btS.print("LED");
      btS.print('n');
      btS.println("is on");
      digitalWrite(L[n-1],HIGH);
    }

    }
    
  }
}
