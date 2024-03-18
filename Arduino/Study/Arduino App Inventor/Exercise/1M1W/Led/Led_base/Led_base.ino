const int L= 10;

void setup(){

  pinMode(L,OUTPUT);
}

void loop(){

  for(int x=0;x<=255;x++){

    analogWrite(L,x);
    delay(10);
  }
}
