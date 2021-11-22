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

    char u = btS.read();

    if(u == '1'){

      btS.println("LED_1 is on");
      digitalWrite(L[0],HIGH);
    }

    else if(u == '2'){

      btS.println("LED_2 is on");
      digitalWrite(L[1],HIGH);
    }

    else if(u == '3'){

      btS.println("LED_3 is on");
      digitalWrite(L[2],HIGH);
    }

    else if(u == '4'){

      btS.println("LED_4 is on");
      digitalWrite(L[3],HIGH);
    }
    else if(u == '5'){

      btS.println("LED_5 is on");
      digitalWrite(L[4],HIGH);
    }

    else if(u=='0'){
      DC();
    }

    
  }
}
