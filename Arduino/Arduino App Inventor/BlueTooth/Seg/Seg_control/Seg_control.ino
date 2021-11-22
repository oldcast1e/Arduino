#include <SoftwareSerial.h>

const int L[7] = {2, 3, 4, 5, 6, 7, 8};
SoftwareSerial btS = SoftwareSerial(9, 10);

const int N[10][7] = {

  {1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 0, 1},
  {1, 1, 1, 1, 0, 0, 1},
  {0, 1, 1, 0, 0, 1, 1},
  {1, 0, 1, 1, 0, 1, 1},
  {1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 1, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1}

};

void DC(){

  for (int n = 0; n <= 6; n++) {
    digitalWrite(L[n], LOW);
  }
}

void setup() {

  btS.begin(9600);

  for (int n = 0; n <= 6; n++) {
    pinMode(L[n], OUTPUT);
  }

  DC();

 }

void loop() {

  if (btS.available() > 0) {

    int u = btS.read();

    for(int x =0;x<7;x++){
      
    if (u == '1') {
      DC();
      digitalWrite(L[x],N[n][x]==1?HIGH:LOW);
    }
    else if (u == '2') {
      DC();
      digitalWrite(L[x], N[n][x]==1?HIGH:LOW);
    }

    else if (u == '3') {
      DC();
      digitalWrite(L[x], N[n][x]==1?HIGH:LOW);
    }

    else if (u == '4') {
      DC();
      digitalWrite(L[x], N[n][x]==1?HIGH:LOW);
    }

    else if(u=='5'){
      DC();
      digitalWrite(L[x],N[n][x]==1?HIGH:LOW);
   }

   else if(u=='6'){
    DC();
      digitalWrite(L[x],N[n][x]==1?HIGH:LOW);
   }

   else if(u=='7'){
    DC();
      digitalWrite(L[x],N[n][x]==1?HIGH:LOW);
   }

   else if(u=='8'){
    DC();
      digitalWrite(L[x],N[n][x]==1?HIGH:LOW);
   }

   else if(u=='9'){
    DC();
      digitalWrite(L[x],N[n][x]==1?HIGH:LOW);
   }

   else if(u=='0'){
    DC();
      digitalWrite(L[x],N[n][x]==1?HIGH:LOW);
   }

  

 }
 
}
}
