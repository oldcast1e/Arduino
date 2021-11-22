const int L[6] ={3,5,6,9,10,11};
const int b = 2;

void setup() {


for(int x=0;x<=6;x++){
  pinMode(L[x],OUTPUT);
 pinMode(b,INPUT);
}
}

void loop() {

 int u = digitalRead(b);
  if(u==HIGH){

   for(int x=0;x<=5;x++){
    for(int x=0;x<=5;x++){
    digitalWrite(L[x],LOW);
   }
    digitalWrite(L[x],HIGH);

    int u = digitalRead(b);
    if(u==LOW) break;
    
    delay(50);
   }
   
  }


  
}
