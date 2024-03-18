const int Lr = 2;
int Lrs = LOW;
const int Ly = 3;
int Lys = LOW;

const int rgb_r = 4;
const int rgb_g = 5;
const int rgb_b = 6;

const int rgb_2_r = 26;
const int rgb_2_g = 25;
const int rgb_2_b = 24;


long pm = 0;
long pm_2 = 0;

long it = 1000;
long it_2 = 1500;

void setup(){

  pinMode(Lr,OUTPUT);
  pinMode(Lr,OUTPUT);

  pinMode(rgb_r,OUTPUT);
  pinMode(rgb_g,OUTPUT);
  pinMode(rgb_b,OUTPUT);

  pinMode(rgb_2_r,OUTPUT);
  pinMode(rgb_2_g,OUTPUT);
  pinMode(rgb_2_b,OUTPUT);
}

void loop(){

  unsigned long nm = millis();

  if (nm - pm>= it){
    pm = nm;
    digitalWrite(Lr,Lrs=(Lrs==LOW?HIGH:LOW));
  }
  if (nm - pm_2>= it_2){
    pm_2 = nm;
    digitalWrite(Ly,Lys=(Lys==LOW?HIGH:LOW));
  }
}
