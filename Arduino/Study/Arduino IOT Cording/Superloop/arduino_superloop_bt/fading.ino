const int L2 = 3;
int L2V = 0;
int L2C = 1;

long pm_2 = 0;
long md_2 = 30;

void fading_setup(){
  pinMode(L2,OUTPUT);
}

void fading_loop(){
  
  unsigned long n2 = millis();
  
  if (n2 - pm_2>=md_2){
    pm_2 = n2;
    
    if(L2C == 1){
      if(L2V<=255){
        L2V +=5;
        if(L2V >255){
          L2V = 255;
          L2C = 0;
      }
    }
    }
    else{
      if(L2V>=0){
        L2V -=5;
        if(L2V <0){
          L2V = 0;
          L2C = 1;
    }
      }
    }
    analogWrite(L2,L2V);
}
}
