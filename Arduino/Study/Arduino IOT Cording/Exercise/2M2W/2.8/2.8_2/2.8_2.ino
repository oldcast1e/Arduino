const int L[2] = {2,3};
int L1s = LOW; //LED1의 상태
int L2s = LOW; //LED2의 상태

const int rgb_1[3] = {22,24,26};
const int rgb_2[3] = {28,30,32};

long pm = 0;
int fadestate = 1;
int fade_1 = 1;


long pm_2 = 0;

long md = 100;
long md_2 = 1500;

void setup(){

  for(int n=0;n<=1;n++){
    pinMode(L[n],OUTPUT);
  }

  for(int m=0;m<=2;m++){
    pinMode(rgb_1[m],OUTPUT);
  }

  for(int r=0;r<=2;r++){
    pinMode(rgb_2[r],OUTPUT);
  }
}

void loop(){

  unsigned long n = millis();
  if (n - pm>=md){
    pm = n;

    if(fadestate==1){
      if (fade_1<=255){
        fade_1+=5;
        if(fade_1>255){
          fade_1=255;
          fadestate =0;
      }
    }
  }
    else{
    if(fade_1>=0){
      fade_1-=5;
      if (fade_1<0){
        fade_1=0;
        fadestate=1;
      }
    }
  }
  analogWrite(L[0],fade_1);
}

  
}
