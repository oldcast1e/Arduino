enum{R5=1,R7,C2,C3,R8,C5,R6,R3,R1,C4,C6,R4,C1,R2,C7,C8}; // 각 위치에 할당값 할당
const unsigned int P[17]={
  -1,10,11,12,13,14,15,16,17,2,3,4,5,6,7,8,9}; //순서대로 각 할당값 할당


const unsigned int R[9]={-1,R1,R2,R3,R4,R5,R6,R7,R8}; //열
const unsigned int C[9]={-1,C1,C2,C3,C4,C5,C6,C7,C8}; //행

void setup() {

 for( int n=1;n<=8;n++){
  pinMode(P[R[n]],OUTPUT);
  pinMode(P[C[n]],OUTPUT);
 }

}

void DL(){

  for( int n=1;n<=8;n++){
  digitalWrite(P[R[n]],HIGH);
  digitalWrite(P[C[n]],HIGH);
 }
}//밑에가 8 위에가 1

void loop() {

  DL();

 for( int n=8;n>=1;n--){
  digitalWrite(P[R[n]],LOW);
  delay(100);
 }

 DL();

 for( int n=1;n<=8;n++){
  digitalWrite(P[R[n]],LOW);
  delay(100);
 }
 

}
