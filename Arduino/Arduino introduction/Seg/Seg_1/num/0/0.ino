const int L[7] = {2,3,4,5,6,7,8};
const int num[7] = {1,1,1,1,1,1,0};

void OS(){

  for(int x =0;x<7; x++){
    pinMode(L[x],OUTPUT);
  }
}

void LL(){

  for(int x =0;x<7; x++){
    digitalWrite(L[x],LOW);
  }
}

void setup() {

OS();
LL();

for(int x =0;x<7; x++){

  digitalWrite(L[x],num[x]==1?HIGH:LOW);
}

}

void loop() {
  

}
