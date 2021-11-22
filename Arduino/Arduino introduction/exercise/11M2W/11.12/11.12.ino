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

void LO(){

for(int x=0;x<7;x++){
  digitalWrite(L[x],LOW);
}
}

void LP(){

for(int x=0;x<7;x++){
  pinMode(L[x],OUTPUT);
}
}

void setup() {

  Serial.begin(115200);
  LP();
}
  
void nF(int n){

 if(0<=n&&n<=9){
   for(int t =0; t<7; t++){
    
      digitalWrite(L[t],N[10][n]==1?HIGH:LOW);
    }   
}
}

void loop() {

  if(Serial.available()){
    char k = Serial.read();

    if('0'<=k&&k<='9'){
      int num = k -'0';

    LO();  
    nF(num);
    }
  }
}
  
