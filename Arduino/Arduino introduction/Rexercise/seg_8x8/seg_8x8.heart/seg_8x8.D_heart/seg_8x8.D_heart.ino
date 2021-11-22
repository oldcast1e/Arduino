enum{R5=1,R7,C2,C3,R8,C5,R6,R3,R1,C4,C6,R4,C1,R2,C7,C8}; // 각 위치에 할당값 할당
const unsigned int P[17]={
  -1,10,11,12,13,14,15,16,17,2,3,4,5,6,7,8,9}; //순서대로 각 할당값 할당


const unsigned int R[9]={-1,R1,R2,R3,R4,R5,R6,R7,R8}; //열
const unsigned int C[9]={-1,C1,C2,C3,C4,C5,C6,C7,C8}; //행

unsigned int r1[9][9]={
  
   {-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,0,0,0,0,0,0,0,0},
  {-1,0,1,1,0,0,1,1,0},
  {-1,1,1,1,1,1,1,1,1},
  {-1,1,1,1,1,1,1,1,1},
  {-1,0,1,1,1,1,1,1,0},
  {-1,0,0,1,1,1,1,0,0},
  {-1,0,0,0,1,1,0,0,0},
  {-1,0,0,0,0,0,0,0,0}
  
};

unsigned int SH[9][9]={

  {-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,0,0,0,0,0,0,0,0},
  {-1,0,0,0,0,0,0,0,0},
  {-1,0,0,1,0,0,1,0,0},
  {-1,0,1,1,1,1,1,1,0},
  {-1,0,0,1,1,1,1,0,0},
  {-1,0,0,0,1,1,0,0,0},
  {-1,0,0,0,0,0,0,0,0},
  {-1,0,0,0,0,0,0,0,0},
};

void DINT(){

  for( int n=1;n<=8;n++){
  pinMode(P[R[n]],OUTPUT);
  pinMode(P[C[n]],OUTPUT);
 }

  for( int k=1;k<=8;k++){
  digitalWrite(P[R[k]],HIGH);
  digitalWrite(P[C[k]],HIGH);
 }
}

void SF(const unsigned int I[9][9]){

  for( int n=1;n<=8;n++){

    if(n>1) digitalWrite(P[R[n-1]],HIGH);
    if(n==1) digitalWrite(P[R[8]],HIGH);

    for(int m=1;m<=8;m++){

      if(I[n][m]==1)
      digitalWrite(P[C[m]],HIGH);
      else digitalWrite(P[C[m]],LOW);
    }

   for(int m=1;m<=8;m++){

      if(I[n][m]==1){
      digitalWrite(P[R[n]],LOW);
      break;   

   }  
  }
  delay(1);
}

}


void setup(){

  DINT();
  
}

void loop(){

  int cnt =0;
  while(true){
    SF(r1);
    cnt++;
    if(cnt==63) break;
  }
  

  cnt =0;
  while(true){
    SF(SH);
    cnt++;
    if(cnt==63) break;
  }
}
