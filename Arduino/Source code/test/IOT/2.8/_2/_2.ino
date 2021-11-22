const int RGB[3] = {44,45,46};
int RGB_state[3] = {LOW,LOW,LOW};

void setup(){

  for(int i=0;i<=2;i++){
    pinMode(RGB[i],OUTPUT);
  }
}

void loop(){

  for(int i =0;i<=2;i++){
     digitalWrite(RGB[i],HIGH);
     for(int x=0;x<=255;x++){
      analogWrite(RGB[i],x);
      delay(10);
     }
  }
}
