const int a = A0;
const int L[6] = { 3,5,6,9,10,11};


void setup() {
 for(int x =0; x<=5;x++){
  pinMode(L[x],OUTPUT);
 }
 
}

void loop() {

int u = analogRead(a);

if( u >1023/7*(1+0))
  digitalWrite(L[0 ],HIGH);
  else digitalWrite(L[0],LOW);

  if( u >1023/7*(1+1))
  digitalWrite(L[1],HIGH);
  else digitalWrite(L[1],LOW);

if( u >1023/7*(1+2))
  digitalWrite(L[2],HIGH);
  else digitalWrite(L[2],LOW);

if( u >1023/7*(1+3))
  digitalWrite(L[3],HIGH);
  else digitalWrite(L[3],LOW);

if( u >1023/7*(1+4))
  digitalWrite(L[4],HIGH);
  else digitalWrite(L[4],LOW);

if( u >1023/7*(1+5))
  digitalWrite(L[5],HIGH);
  else digitalWrite(L[5],LOW);        
}
