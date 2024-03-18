#include <SoftwareSerial.h>

const int L[5] = {2, 3, 4, 5, 6};

SoftwareSerial btS = SoftwareSerial(9, 10);

void DC() {

  for (int x = 0; x <= 4; x++) {
    digitalWrite(L[x], LOW);
  }
}


void setup() {

  for (int x = 0; x <= 4; x++) {
    pinMode(L[x], OUTPUT);
  }

  Serial.begin(9600);
  btS.begin(9600);

  DC();
}

void loop() {

  if (btS.available() > 0) {

    char u = btS.read();

    if (u == '1') {

      btS.println("LED on");

      for (int n = 0; n <= 4; n++) {
        for(int x =0;x<=4;x++){
          digitalWrite(L[x],LOW);
        }
      digitalWrite(L[n],HIGH);
      delay(100);
      
      }

    }

    else if (u == '0') {
      DC();
    }
  }
}
