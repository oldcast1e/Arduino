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

void DL(){

  for(int x=0;x<7;x++){
    digitalWrite(L[x],LOW);
  }
}

void DP(){

 for(int x=0;x<7;x++){
    pinMode(L[x],OUTPUT);

}
}

void NF(int n){

  if(0<=n&&n<=9){

    for(int x=0; x<7;x++){
      digitalWrite(L[x],N[n][x]==1?HIGH:LOW);
    }
  }
}
void setup() {
 
Serial.begin(115200);
DP();
}

void loop() {

if(Serial.available()){

    char a = Serial.read();
  
    if('0'<=a&&a<='9'){
     int k = a - '0'; 
     DL(); 
     NF(k);
    }
}

}
