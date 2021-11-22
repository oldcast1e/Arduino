int k =0;
int t = 1000;
int m = 0;

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

  if(0<=n && n<=9 && 1<=m&&m<=4){
    for(int x=0;x<7;x++){
      digitalWrite(L[x],N[n][x]==1?HIGH:LOW);
    }
    digitalWrite(com[m],LOW);
  }
  
}
void setup(){

  lcint();
  Serial.begin(115200);
  NF(0,1);
  NF(0,2);
  NF(0,3);
  NF(0,4);
}

void loop(){

  unsigned int now = millis();
  if (now >= t){
    unsigned int k1 = k/600;
    unsigned int k2 = k%60;
    unsigned int k3 = k%10;
    unsigned int k4 = k/10;
      
    NF(k1,1);
    delay(1);
    NF(k2,2);
    delay(1);
    NF(k3,3);
    delay(1);
    NF(k4,4);
    delay(1);    
  }
  NF(t)
  t += 1000;
  k+=1;  
} 
