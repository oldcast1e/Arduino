#include<SoftwareSerial.h>

SoftwareSerial btS = SoftwareSerial(9,10);

int b1= 7;
int b2 = 6;
int b3 = 5;

int IF1(int k){

  static int o = 1;
  static int n = 1;

  n = digitalRead(k);

  if(o != n){
    o = n;
    if(n==0){
      delay(200);
      return 1;
    }
  }
  return 0;
}

int IF2(int k){

  static int o = 1;
  static int n = 1;

  n = digitalRead(k);

  if(o != n){
    o = n;
    if(n==0){
      delay(200);
      return 1;
    }
  }
  return 0;
}

int IF3(int k){

  static int o = 1;
  static int n = 1;

  n = digitalRead(k);

  if(o != n){
    o = n;
    if(n==0){
      delay(200);
      return 1;
    }
  }
  return 0;
}
void setup(){

  btS.begin(9600);

  pinMode(b1,INPUT_PULLUP);
  pinMode(b2,INPUT_PULLUP);
  pinMode(b3,INPUT_PULLUP);
}

void loop(){

  if(IF1(b1)==1){
    btS.println("b1");
  }
  else if(IF1(b2)==1){
    btS.println("b2");
  }
  else if(IF1(b3)==1){
    btS.println("b3");
  }
}
