const int L[7]= {2,3,4,5,6,7,8}; //LED
const int C[1+4] = {-1,9,10,11,12}; //com

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

void DP(){

  for(int x =0; x<7;x++){
    pinMode(L[x],OUTPUT);
  }
}

void CP(){

  for(int y =1; y<=4; y++){
    pinMode(C[y],OUTPUT);
  }
}

void DCL(){
for(int x=0 ; x<7; x++){
    digitalWrite(L[x],LOW);
  }

for(int y =1; y<=4; y++){
    digitalWrite(C[y],HIGH);
  }  
  
}

void NF(unsigned int n, unsigned int m){

  DCL();
  
  if(0<=n&&n<=9 && 1<=m&&m<=4){
    for(int t =0 ; t< 7; t++){

      digitalWrite(L[t],N[n][t]==1?HIGH:LOW);
    }
    digitalWrite(C[m],LOW);
  }

  
}

void setup() {

 DP();
 CP();
}

void loop() {

  NF(1,1);
  delay(500);

  NF(2,2);
  delay(500);

  NF(3,3);
  delay(500);

  NF(4,4);
  delay(500);

  
  
}
