const int L =13;
const int b = 2;

void setup(){

  Serial.begin(115200);
  pinMode(L,OUTPUT);
  pinMode(b,INPUT);
  
}

void loop(){

int d = digitalRead(b);
Serial.println(d);
 digitalWrite(L,d);
 }
