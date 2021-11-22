const unsigned int L[12]={2,3,4,5,6,7,8,9,10,11,12,13};

void setup(){

  for(int x =0 ;x<=12; x++){
    pinMode(L[x],OUTPUT);
  }
  
}

void loop(){
    for(int x= 0;x<=12;x++){
    digitalWrite(L[x],LOW);
  }
  delay(50);
  
  for(int x= 0;x<=12;x++){
  digitalWrite(L[x],HIGH);

  delay(50);
}


}
