const int L[6] = {3,5,6,9,10,11};
const int o = A0;

void setup() {

 for(int x=0; x<=5 ; x ++){
  pinMode(L[x],OUTPUT);
 }

}

void loop() {

int u = analogRead(o);

for(int n=0; n <= 5; n ++){

if(u> 1023/7*(1+n))

for(int k=0; k<=255; k++){
  analogWrite(L[n],k);
  delay(5);
  }

else digitalWrite(L[n],LOW);

else if(
}
 
}
