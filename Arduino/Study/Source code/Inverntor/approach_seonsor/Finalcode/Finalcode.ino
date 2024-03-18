const unsigned int tp = 11;
const unsigned int ep = 12;

const int buz = 10;
int buzstate = LOW;
void setup(){

  pinMode(tp,OUTPUT);
  pinMode(ep,INPUT);

  pinMode(buz,OUTPUT);
  
  Serial.begin(112500);
}

void loop(){

  digitalWrite(tp,LOW);
  delayMicroseconds(2);

  digitalWrite(tp,HIGH);
  delayMicroseconds(10);
  digitalWrite(ep,LOW);

  long d = pulseIn(ep,HIGH);
  long D = (d / 2) / 29.1;


  delay(10);
  if (D < 80) {
    
    delay(100);
    buzstate = (buzstate == LOW) ? HIGH : LOW;
    if (buzstate == LOW) {
      digitalWrite(buz,LOW);
    }
    else if (buzstate == HIGH) {
      digitalWrite(buz,HIGH);

    }

  
  }
  
  else if(80<=D){

    buzstate == LOW;
    digitalWrite(buz,LOW);
    
  }
    
}
