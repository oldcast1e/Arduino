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

    String sd = btS.readStringUntil('\n');

    if (sd.startsWith("R1")==1) {
    digitalWrite(R, HIGH);
    }
    else if (sd.startsWith("R0")==1)  {
    digitalWrite(R, LOW);
    }
    else if (sd.startsWith("G1")==1)  {
    digitalWrite(G, HIGH);
    }
    else if (sd.startsWith("G0")==1)  {
    digitalWrite(G,LOW);
    }
    else if (sd.startsWith("B1")==1)  {
    digitalWrite(B, HIGH);
    }  
    else if (sd.startsWith("B0")==1)  {
    digitalWrite(B, LOW);
    }

  }
}
