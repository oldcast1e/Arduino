const int RGB2[3] = {32,30,28};

int fadeval[3] = {0};
int fadedir[3] = {1,1,1};

int RGB_prv[3] = {0};
int duration_RGB[3] = {30,60,120};

void RGB_fading_setup(){
   for(int i=0;i<3;i++){
    pinMode(RGB[i],OUTPUT);
   }
} 

void RGB_fading_loop(){

  unsigned int rgbct = millis();
  for(int i=0;i<3;i++){
    if(rgbct - RGB_prv[i] >= duration_RGB[i]){
      RGB_prv[i] = rgbct;

      if(fadedir[i]==1){
        if(fadeval[i] == 255) fadedir[i] = 0;
        else if(fadeval[i]<256) fadeval[i] += 5;
      }
      else if(fadedir[i]==0){
        if(fadeval[i] == 0) fadedir[i] = 1;
        else if(fadeval[i]>0) fadeval[i] -= 5;
      }
      analogWrite(RGB2[i],fadeval[i]);

      
    }
  }
  
}
