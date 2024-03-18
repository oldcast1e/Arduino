int fadRGB[3]={44,45,46};
int fadvalue[3] = {0,0,0};
int faddir[3] = {1,1,1};

long pm[3] = {0,};
long dm[3] = {30,60,120};

void setup(){}

void loop(){

  unsigned long n = millis();

  for(int i=0;i<=2;i++){
    
  
    if(n -pm[i]>=dm[i]){
      pm[i] = n;

      if(faddir[i] ==1){
        if(fadvalue[i]<=255){
          fadvalue[i] +=5;
          if(fadvalue[i]>255){
            fadvalue[i] = 255;
            faddir[i] =0;
          }
        }
      }else{
        if(fadvalue[i]>=0){
          fadvalue[i] -=5;
          if(fadvalue[i]<0){
            fadvalue[i] = 0;
            faddir[i] =1;
      }
    }
    
  }
  analogWrite(fadRGB[i],fadvalue[i]);
}
  }
}
