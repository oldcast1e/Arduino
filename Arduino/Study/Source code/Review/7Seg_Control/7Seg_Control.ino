const int seg[7] = {2,3,4,5,6,7,8};

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

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<7;i++){
    pinMode(seg[i],OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int j=0;j<10;j++){
    for(int i=0;i<7;i++){
      digitalWrite(seg[i],N[j][i]==1?HIGH:LOW);
    }
    delay(1000);
    for(int i=0;i<7;i++){
      digitalWrite(seg[i],LOW);
    }
  }

}
