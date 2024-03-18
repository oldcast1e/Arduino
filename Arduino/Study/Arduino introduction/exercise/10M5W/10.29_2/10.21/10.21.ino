const int L = 10;
const int b = 2;

void setup(){

  pinMode(b,INPUT);
  Serial.begin(115200);
}

void loop(){

  int d = digitalRead(b);
  Serial.println(d);
  

  if(d==HIGH){

    for(int i=0;i<=255;i++){
      analogWrite(L,i); 
      delay(100);
    }
  }
    else {
    analogWrite(L,0);
  }
}
