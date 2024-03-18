int bls = LOW;
int bm = 0 ;
int bitv = 1000;

const int LED1 = 2;

const int B1 = 22;
int B1S = LOW;

void blink_setup(){
  pinMode(LED1,OUTPUT);
}

void blink_loop(){
  B1S = digitalRead(B1);

  if(B1S == LOW){
    digitalWrite(LED1,LOW);
    return;
  }

  unsigned long n = millis();

  if(n-bm>bitv){

    bm = n;
    digitalWrite(LED1,bls=(bls==LOW?HIGH:LOW));
    
  }
}
