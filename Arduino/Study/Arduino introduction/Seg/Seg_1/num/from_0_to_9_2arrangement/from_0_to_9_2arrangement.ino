const int L[7] = {2,3,4,5,6,7,8};

const int N[10][7]={
  
{1,1,1,1,1,1,0},
{0,1,1,0,0,0,0},
{1,1,0,1,1,0,1},
{1,1,1,1,0,0,1},
{0,1,1,0,0,1,1},
{1,0,1,1,0,1,1},
{1,0,1,1,1,1,1},
{1,1,1,0,0,1,0},
{1,1,1,1,1,1,1},
{1,1,1,1,0,1,1}

};

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

void NA(int n){
  

  if(0<=n&&n<=9){
    for(int x =0; x<7;x++){
      digitalWrite(L[x],N[n][x]==1?HIGH:LOW);
    }
  }
}

void loop() {

for(int n=0;n<=9;n++){
  LL();
  NA(n);
  delay(500);
  
}

}
