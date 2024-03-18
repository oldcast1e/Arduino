const int Bs = 10;
const int mel[8] = {262,294,330,349,392,440,494,523};
void setup() {
  // put your setup code here, to run once:
  pinMode(Bs,OUTPUT);
  for(int i=0;i<8;i++){
    tone(Bs,mel[i]);
    delay(1000);

    noTone(Bs);
  }
//    tone(Bs,mel[6]);
//    delay(1000);
//    noTone(Bs);

  

}

void loop() {
  // put your main code here, to run repeatedly:
  

}
