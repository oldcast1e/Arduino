const unsigned int L[6] = {3,4,5,6,7,8};

void setup() {
  
for(int x =0 ; x<7 ; x++){
pinMode(L[x],OUTPUT);
}
}

void loop() {

 for(int x =0 ; x<6 ; x++){
  
  for(int x =0 ; x<6 ; x++){
    digitalWrite(L[x],LOW);
  }
   
    digitalWrite(L[x],HIGH);
    delay(100);


}
}
