long pm = 0;
long md = 1000;

const int L1 = 2;
int L1S = LOW;

void blink_setup(){
  pinMode(L1,OUTPUT);
}

void blink_loop(){
  unsigned long n = millis();
  if (n - pm>=md){
    pm = n;

    digitalWrite(L1,L1S=(L1S==LOW?HIGH:LOW));
  }

}
