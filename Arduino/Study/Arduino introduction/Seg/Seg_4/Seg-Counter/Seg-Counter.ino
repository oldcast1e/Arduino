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

void DNF(unsigned int num){

  unsigned num_1000 = num/1000;
  unsigned num_100 = (num%1000)/100;
  unsigned num_10 = (num%100)/10;
  unsigned num_1 = num%10;

  NF(num_1000,1);
  delay(1);
  NF(num_100,2);
  delay(1);
  NF(num_10,3);
  delay(1);
  NF(num_1,4);
  delay(1);

  

  
}

void setup() {

 DP();
 CP();
}

void loop() {

 static unsigned int num = 0;
 num ++; 
 DNF(num);
  
  
}
