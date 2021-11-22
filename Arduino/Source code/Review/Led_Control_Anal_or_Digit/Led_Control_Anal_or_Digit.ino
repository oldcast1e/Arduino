const int la[5] = {3,5,6,9,10};
int cnt = 0;


void setup() {
  // put your setup code here, to run once:
  for(int i = 0;i<5;i++){
    pinMode(la[i],OUTPUT);
  }
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){

    char u = Serial.read();
    if(u == 'a'){

     
      for(int i=0;i<5;i++){
        for(int j=0;j<256;j++){
          analogWrite(la[i],j);
          delay(5);
        }
        
      }
      for(int i=4;i>=0;i--){
        for(int j=254;j>=0;j--){
          analogWrite(la[i],j);
          delay(5);
        }
        
      }
    }
    else if(u == 'd'){

      for(int i=0;i<5;i++){
        for(int j=0;j<5;j++) digitalWrite(la[j],LOW);
        digitalWrite(la[i],HIGH);
        delay(1000);
      }

    }

  else if(u=='b') for(int j=0;j<5;j++) digitalWrite(la[j],LOW);
    
  }

}
