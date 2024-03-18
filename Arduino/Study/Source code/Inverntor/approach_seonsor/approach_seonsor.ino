const unsigned int tp = 11;
const unsigned int ep = 12;

const int buz = 10;
int buzst_1 = LOW;
int buzst_2 = LOW;

long pm_1 = 1000;
long dt_1 = 0;
long pm_2 = 500;
long dt_2 = 0;

void WF(int n){

  if(5<= n <15){
    digitalWrite(buz,HIGH);
    delay(500); 
    digitalWrite(buz,LOW);
    delay(500); 
  }
  else if(15<= n <30){
    digitalWrite(buz,HIGH);
    delay(1000); 
    digitalWrite(buz,LOW);
    delay(1000); 
  }
  else
    digitalWrite(buz,LOW);
}

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

  delay(100);
  if (5<=D<15) {
    delay(1000);
    long n = millis();
    if(n-pm_1>=dt_1){
      digitalWrite(buz,buzst_1=(buzst_1==LOW?HIGH:LOW));
    }
    
    }
    
  Serial.print("Distance: ");
  Serial.print(D);
  Serial.println(" cm");
  
}
