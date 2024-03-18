long pm_3[3] = {0,};
long md_3[3] = {1000,2000,3000};

const int RGB[3] = {A8,A9,A10};
int RGBS[3] = {LOW,LOW,LOW};

void RGBblink_setup(){
  
  for(int i=0;i<=2;i++){
    pinMode(RGB[i],OUTPUT);
  }
}

void RGBblink_loop(){
  
  unsigned long n = millis();
  
  for(int i=0;i<=2;i++){
    
    if (n - pm_3[i] >= md_3[i]){     
    pm_3[i] = n;
    digitalWrite(RGB[i],RGBS[i]=(RGBS[i]==LOW?HIGH:LOW));
    }
  }
}
