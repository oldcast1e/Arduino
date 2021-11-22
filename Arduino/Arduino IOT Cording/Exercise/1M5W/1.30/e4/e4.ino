const int L1 = 2;
const int L2 = 3;

long dv1 = 1000;
long dv2 = 500;

long nv1 = 0;
long nv2 = 0;

int Ls1 = HIGH;
int Ls2 = LOW;

void LI1(){
  pinMode(L1,OUTPUT);
  digitalWrite(L1,LOW);
}
void LF1(){
  
  unsigned long now1 = millis();
  if (now1 - nv1 >= dv1){
    nv1 = now1;

    digitalWrite(L1,Ls1=(Ls1==LOW?HIGH:LOW));
  }
}

void LI2(){
  pinMode(L2,OUTPUT);
  digitalWrite(L2,LOW);
}
void LF2(){
  
  unsigned long now2 = millis();
  if (now2 - nv2 >= dv2){
    nv2 = now2;

    digitalWrite(L2,Ls2=(Ls2==LOW?HIGH:LOW));
  }
}

void setup(){
  LI1();
  LI2();
}

void loop(){
  LF1();
  LF2();
}
