unsigned long tp = 0;
const unsigned int d = 1000;

const unsigned int L[8] = {2,3,4,5,6,7,8,9};
const unsigned int com[5] = {-1,9,10,11,12};

const unsigned int N[10][7]={
  {1,1,1,1,1,1,0},
  {0,1,1,0,0,0,0},
  {1,1,0,1,1,0,1},
  {1,1,1,1,0,0,1},
  {0,1,1,0,0,1,1},
  {1,0,1,1,0,1,1},
  {1,0,1,1,1,1,1},
  {1,1,1,0,0,1,0},
  {1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1},
};

void lcint(){

  for(int n = 0;n<7;n++){
    pinMode(L[n],OUTPUT);
  }

  for(int n = 1;n<=4;n++){
    pinMode(com[n],OUTPUT);
  }
}

void lcc(){
  for(int n = 0;n<7;n++){
    digitalWrite(L[n],LOW);
  }

  for(int n =1;n<=4;n++){
    digitalWrite(com[n],HIGH);
  }
}

void NF(unsigned int n,unsigned int m ){
  lcc();
  digitalWrite(com[m],LOW);
  
    for(int x=0;x<7;x++){
      digitalWrite(L[x],N[n][x]==1?HIGH:LOW);
    }
    
  digitalWrite(com[m],HIGH);
}
  

void setup(){

  lcint();
  Serial.begin(115200);
}

void loop(){ //k의 초기값: 0, t의 초기값:1000
  unsigned long now = millis();
  if(now - tp >= 1000){
    tp = now;

    int T = now*0.001;
    

    int minute1 = T/60/10;
    int minute2 = T/60%10;
    int second1 = T%60/10;
    int second2 = T%60%10;
    
    NF(second2,4);
    NF(second1,3);
    NF(second2,2);
    NF(second1,1);
     
  }
  
}
  
