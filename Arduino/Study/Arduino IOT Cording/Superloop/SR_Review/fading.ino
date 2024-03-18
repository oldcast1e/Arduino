const int LED2 = 5;

int prv2 = 0;
int duration2 = 50;

int cnt = 0;
int ledval = 0;

void fading_setup(){
  pinMode(LED2,OUTPUT);
  
}

void fading_loop(){

  unsigned int ct2 = millis();
  if(ct2 - prv2 >= duration2){
    prv2 = ct2;

    if(cnt==0){
      if(ledval == 255) cnt = 1;
      else if(ledval<256) ledval += 5;
      
    }
    else if(cnt==1){
      if(ledval==0) cnt = 0;
      else if(ledval>0) ledval -= 5;
    }

    analogWrite(LED2,ledval);
  }
  
}
