const int L[7]={2,3,4,5,6,7,8};

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

  for(int x=0;x<=6;x++){

    pinMode(L[x],OUTPUT);
  }
}

void DC(){
   for(int x=0;x<=6;x++){

    digitalWrite(L[x],LOW);
   }
}

void DF(int n){

  if(0<=n&&n<=9){

    for(int x=0;x<=6;x++){

      digitalWrite(L[x],N[n][x]==1?HIGH:LOW);
    }
  }
}

void setup(){

  DP();
}

void loop(){

  for(int n=0;n<=9;n++){

    DC();
    DF(n);
    delay(1000);
  }
}
