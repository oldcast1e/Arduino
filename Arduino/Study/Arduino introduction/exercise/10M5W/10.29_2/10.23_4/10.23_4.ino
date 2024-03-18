const int L[6] = {3,5,6,9,10,11};
const int b = 2;

void setup() {
  
pinMode(b,INPUT);

for(int x=0;x<=5;x++){
pinMode(L[x],OUTPUT);
}

}


void loop(){

int d = digitalRead(b);
if(d==HIGH){

  for(int x=0;x<=5;x++){

    
    for(int x=0;x<=5;x++){
    digitalWrite(L[x],LOW);
  }
  
    digitalWrite(L[x],HIGH);
  
  int g = digitalRead(b);
  if(g==LOW)  break;
  delay(50);
}
}



}
