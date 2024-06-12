const int seg[8] = {2,3,4,5,6,7,8,9};

const int N[10][7] = {
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

const int DOT[11][8] = {
  {1,1,1,1,1,1,0,0},
  {0,1,1,0,0,0,0,0},
  {1,1,0,1,1,0,1,0},
  {1,1,1,1,0,0,1,0},
  {0,1,1,0,0,1,1,0},
  {1,0,1,1,0,1,1,0},
  {1,0,1,1,1,1,1,0},
  {1,1,1,0,0,1,0,0},
  {1,1,1,1,1,1,1,0},
  {1,1,1,1,0,1,1,0},
  {0,0,0,0,0,0,0,1} 

};

const int Birth[4] = {0,7,0,5};

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<7;i++){
    pinMode(seg[i],OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int k  = 0; k< 4 ; k++){
      int j = Birth[k];
      for(int i=0;i<7;i++){digitalWrite(seg[i],N[j][i]==1?HIGH:LOW);}
      delay(1000);
      for(int i=0;i<7;i++){digitalWrite(seg[i],LOW);}
  }

}