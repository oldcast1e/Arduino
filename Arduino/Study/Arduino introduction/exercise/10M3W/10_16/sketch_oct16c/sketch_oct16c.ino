int unsigned L[6] = {3,5,6,9,10,11};

void setup(){
 
}

void loop(){

for(int n=0;n<=5;n++){

  for(int t=0;t<=255;t++){
    analogWrite(L[n],t);
    delay(2);
    
  }
}

for(int n=5;n>=0;n--){

  for(int t=255;t>=0;t--){
    pinMode(L[n],OUTPUT);

    analogWrite(L[n],t);
    delay(2);
  }
}

delay(500);
}
