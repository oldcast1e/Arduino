const int t[8] = {262,294,330,349,440,494,523};
const int b[8] = {2,3,4,5,6,7,8,9};

const int s = 10;

void setup() {

 for ( int x=0;x<=7; x++){
  pinMode(b[x],INPUT);
 }

}

void loop() {

 if(digitalRead(b[0])==HIGH){
  tone(s,t[0]);
 }

 else if(digitalRead(b[1])==HIGH){
  tone(s,t[1]);
 }
 else if(digitalRead(b[2])==HIGH){
  tone(s,t[2]);
 }
 else if(digitalRead(b[3])==HIGH){
  tone(s,t[3]);
 }
 else if(digitalRead(b[4])==HIGH){
  tone(s,t[4]);

 }
 else if(digitalRead(b[5])==HIGH){
  tone(s,t[5]);
 }
 else if(digitalRead(b[6])==HIGH){
  tone(s,t[6]);
 }

 else if(digitalRead(b[7])==HIGH){
  tone(s,t[7]);
 }

 else {noTone(s);
}
}
