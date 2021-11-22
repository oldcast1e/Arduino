const int L1 = 2;
const int b1 = 22;

int L1s = LOW; //LED의 상태
int ledstate = 0;

long blpm = 0;
long bldt = 500;

long pm_L1 = 0;
long dt_L1 = 1000;

void blink_setup(){
  
  pinMode(L1,OUTPUT);
  pinMode(b1,INPUT);
  
}

void L1F(int ls){

  if(ls==1){

    long n_L1 = millis();
    
    if(n_L1 - pm_L1>=dt_L1){

      pm_L1 = n_L1;
      digitalWrite(L1,L1s=(L1s==LOW?HIGH:LOW));
    }
  }
  else 
    digitalWrite(L1,LOW);
  
}
void blink_loop(){
      
    long bln = millis();
    
    if(bln - blpm>=bldt){
      blpm = bln;
      if(digitalRead(b1)==1){
        ledstate = 1;
      }
      else if(digitalRead(b1)==0){
        ledstate = 0;
      }
      L1F(ledstate);
      Serial.println(ledstate);
    }
  
}
