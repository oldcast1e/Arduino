#include <SoftwareSerial.h>

SoftwareSerial btS = SoftwareSerial(9, 10);

int R = 6;
int G = 5;
int B = 3;

void setup() {

  btS.begin(9600);

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {

  if (btS.available() > 0) {

      int u = btS.read();

        if(u=='1'){
          digitalWrite(R,HIGH);
        }
        else if(u=='2'){
          digitalWrite(R,LOW);
        }
        if(u=='3'){
          digitalWrite(G,HIGH);
        }
        else if(u=='4'){
          digitalWrite(G,LOW);
        }
        if(u=='5'){
          digitalWrite(B,HIGH);
        }
        else if(u=='6'){
          digitalWrite(B,LOW);
        }
        else if(u=='7'){
          digitalWrite(R,LOW);
          digitalWrite(G,LOW);
          digitalWrite(B,LOW);
        }

        else if(u=='8'){
          digitalWrite(R,HIGH);
          digitalWrite(G,HIGH);
          digitalWrite(B,HIGH);
        }
      
      
  }
}
