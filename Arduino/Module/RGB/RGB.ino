long pm_3[3] = {0,};
long md_3[3] = {1000,2000,3000};

const int RGB[3] = {9,10,11};
int RGBS[3] = {LOW,LOW,LOW};

void turnoff(){
  digitalWrite(RGB[0],LOW);
  digitalWrite(RGB[1],LOW);
  digitalWrite(RGB[2],LOW);
}

void setup(){
  
  for(int i=0;i<=2;i++){
    pinMode(RGB[i],OUTPUT);
  }
}

void loop(){
  
  for(int i=0;i<3;i++){
    digitalWrite(RGB[i],HIGH);
    delay(1000);
    turnoff();
  }
}
