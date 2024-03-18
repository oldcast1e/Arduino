const int LED1 = 7;

int duration = 1000;
int prv = 0;
bool ls = LOW;

void blink_setup(){
  pinMode(LED1,OUTPUT);
  
}

void blink_loop(){

  unsigned int ct = millis();
  if(ct - prv>= duration){

    prv = ct;
    digitalWrite(LED1,ls);
    ls = (ls==HIGH?LOW:HIGH);
  }
}
