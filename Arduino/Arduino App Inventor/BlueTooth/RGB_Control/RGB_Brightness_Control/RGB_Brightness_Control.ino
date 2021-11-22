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
          analogWrite(R,255);
        }
        else if(u=='2'){
         analogWrite(R,100);
        }
        if(u=='3'){
          analogWrite(R,0);
        }
             
      
  }
}
