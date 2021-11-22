const unsigned int L[7]={2,3,4,5,6,7,8};

const unsigned int C[5]={-1,9,10,11,12};

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

void DP(){

  for(int x=0;x<=6;x++){

    pinMode(L[x],OUTPUT);
  }

  for(int y=1;y<=4;y++){

    pinMode(C[y],OUTPUT);
  }
  
}

void DC(){

  for(int x=0;x<7;x++){

    digitalWrite(L[x],LOW);
  }

  for(int y=1;y<=4;y++){

    digitalWrite(C[y],HIGH);
  }
  }

void DF(unsigned int n, unsigned int m){

DC();

if(0<=n&&n<=9 && 1<=m&&m<=4){

  for(int x=0;x<7;x++){

    digitalWrite(L[x],N[n][m]==1?HIGH:LOW);
  }
  digitalWrite(C[m],LOW);
  }
}


void setup(){

  DP();
}

void loop(){

  DF(1,1);
  delay(500);
  DF(2,2);
  delay(500);
  DF(3,3);
  delay(500);
  DF(4,4);
  delay(500);
}
  
