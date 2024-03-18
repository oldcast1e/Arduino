const int L[7] = {2,3,4,5,6,7,8};

const int N0[7] = {1,1,1,1,1,1,0};
const int N1[7] = {0,1,1,0,0,0,0};
const int N2[7] = {1,1,0,1,1,0,1};
const int N3[7] = {1,1,1,1,0,0,1};
const int N4[7] = {0,1,1,0,0,1,1};
const int N5[7] = {1,0,1,1,0,1,1};
const int N6[7] = {1,0,1,1,1,1,1};
const int N7[7] = {1,1,1,0,0,1,0};
const int N8[7] = {1,1,1,1,1,1,1};
const int N9[7] = {1,1,1,1,0,1,1};

void OS(){

  for(int x =0;x<7; x++){
    pinMode(L[x],OUTPUT);
  }//아웃풋 정의
}

void LL(){

  for(int x =0;x<7; x++){
    digitalWrite(L[x],LOW);
  }
}// LED 모두 끄기

void setup() {

OS();

}

void loop() {

LL();
for(int x =0;x<7; x++){
  digitalWrite(L[x],N0[x]==1?HIGH:LOW);
}
delay(100);

LL();
for(int x =0;x<7; x++){
  digitalWrite(L[x],N1[x]==1?HIGH:LOW);
}
delay(100);

LL();
for(int x =0;x<7; x++){
  digitalWrite(L[x],N2[x]==1?HIGH:LOW);
}
delay(1000);

LL();
for(int x =0;x<7; x++){
  digitalWrite(L[x],N3[x]==1?HIGH:LOW);
}
delay(1000);

LL();
for(int x =0;x<7; x++){
  digitalWrite(L[x],N4[x]==1?HIGH:LOW);
}
delay(1000);

LL();
for(int x =0;x<7; x++){
  digitalWrite(L[x],N5[x]==1?HIGH:LOW);
}
delay(1000);

LL();
for(int x =0;x<7; x++){
  digitalWrite(L[x],N6[x]==1?HIGH:LOW);
}
delay(1000);

LL();
for(int x =0;x<7; x++){
  digitalWrite(L[x],N1[x]==1?HIGH:LOW);
}
delay(1000);

LL();
for(int x =0;x<7; x++){
  digitalWrite(L[x],N7[x]==1?HIGH:LOW);
}
delay(1000);

LL();
for(int x =0;x<7; x++){
  digitalWrite(L[x],N8[x]==1?HIGH:LOW);
}
delay(1000);

LL();
for(int x =0;x<7; x++){
  digitalWrite(L[x],N9[x]==1?HIGH:LOW);
}
delay(1000);


  

}
