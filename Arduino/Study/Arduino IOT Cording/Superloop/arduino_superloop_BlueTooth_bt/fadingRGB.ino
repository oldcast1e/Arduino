int RGB_2[3] = {A0,A1,A2};
int RGBV[3] = {0,};
int RGBC[3] = {1,1,1};

long pm_4[3] = {0,};
long dm_4[3] = {30,60,120};

void fadingRGB_setup(){

  for(int i=0;i<=2;i++){
    pinMode(RGB_2[i],OUTPUT);
  }
}

void fadingRGB_loop(){

  unsigned long n = millis();

  for(int i=0;i<=2;i++){

    if(n - pm_4[i] >= dm_4[i]){

       pm_4[i] = n;

       if(RGBC[i] == 1){
        if(RGBV[i]<=255){
          RGBV[i]+=5;
          if(RGBV[i] > 255){
            RGBV[i] = 255;
            RGBC[i] = 0; 
          }
        }
       }
       else{
        if(RGBV[i]>=0){
          RGBV[i]-=5;
          if(RGBV[i] < 0){
            RGBV[i] = 0;
            RGBC[i] = 1; 
          }
        }
       }
       analogWrite(RGB_2[i],RGBV[i]);
    }
  }
}
