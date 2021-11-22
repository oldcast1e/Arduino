const int L[6] = {3,5,6,9,10,11};

void setup(){
  
}
void loop(){

   for(int x=0; x<=225;x ++){
    pinMode(L[0],OUTPUT);
    analogWrite(L[0],x);
    delay(10);
    analogWrite(L[0],0);
  }

  for(int x=0; x<=225;x ++){
    pinMode(L[1],OUTPUT);
    analogWrite(L[1],x);
    delay(10);
     analogWrite(L[1],0);
  }

  for(int x=0; x<=225;x ++){
    pinMode(L[2],OUTPUT);
    analogWrite(L[2],x);
    delay(10);
     analogWrite(L[2],0);
  }

  for(int x=0; x<=225;x ++){
    pinMode(L[3],OUTPUT);
    analogWrite(L[3],x);
    delay(10);
     analogWrite(L[3],0);
  }

  for(int x=0; x<=225;x ++){
    pinMode(L[4],OUTPUT);
    analogWrite(L[4],x);
    delay(10);
     analogWrite(L[4],0);
  }

  for(int x=0; x<=225;x ++){
    pinMode(L[5],OUTPUT);
    analogWrite(L[5],x);
    delay(10);
     analogWrite(L[5],0);
  }

  for(int x=0; x<=225;x ++){
    pinMode(L[6],OUTPUT);
    analogWrite(L[6],x);
    delay(10);
     analogWrite(L[6],0);

     
  }

 
}
