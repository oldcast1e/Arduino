int bls = LOW;
int bm = 0 ;
int bitv = 1000;

const int LED1 = 2;

const int B = 22;
int B1S = LOW;

void blink_setup(){
  pinMode(LED1,OUTPUT);
  pinMode(B1,INPUT);
}

void blink_loop(){
  B1S = digitalRead(B);

  if(B1S == LOW){
    digitalWrite(LED1,LOW);
    return;
  }

  unsigned long n = millis();

  if(n-bm>bitv){

    bm = n;
    if(bls = LOW){
      bls = HIGH;
    }
    else if(bls = HIGH){
      bls = LOW;
    }
    digitalWrite(LED1,bls);
  }
}
