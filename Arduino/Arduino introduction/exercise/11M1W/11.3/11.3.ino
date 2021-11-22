const int s = 10;
const int b =2;

int LS = LOW;
int LC = false;

void bp(){
  LS=(LS==LOW)?HIGH:LOW;
  LC = true;
}
void setup() {
pinMode(s,OUTPUT);
pinMode(b,INPUT);

attachInterrupt(digitalPinToInterrupt(b),bp,RISING);

}

void loop() {

  if(LC){
    LC=false;
    digitalWrite(s,LS);
  }


}
