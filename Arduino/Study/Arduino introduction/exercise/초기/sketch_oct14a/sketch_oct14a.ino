const int L = 13;

void setup(){

  pinMode(L,OUTPUT);
  Serial.begin(115200);
}

void loop(){

for(int t=0;t<=10;t++){

  int c=0;
  while(true){

    digitalWrite(L,HIGH);
    delay(t);
    digitalWrite(L,LOW);
    delay(10-t);

    c ++;
    if(c==10) break;
    }

  

  
}
  
}
