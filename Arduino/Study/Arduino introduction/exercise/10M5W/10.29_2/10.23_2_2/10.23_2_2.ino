const int b =2;
const int L =10;

void setup() {

 pinMode(b,INPUT);
 pinMode(L,OUTPUT);
}

void loop() {

int d = digitalRead(b);
if(d==HIGH){

  for(int t=0; t<=255;t++){
    analogWrite(L,t);
    delay(5);
  }

}
else{
    digitalWrite(L,0);
  }

}
