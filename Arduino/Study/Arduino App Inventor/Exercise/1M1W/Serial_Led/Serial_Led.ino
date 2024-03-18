const int L= 10;

void setup(){

  Serial.begin(115200);
  pinMode(L,OUTPUT);
}

void loop(){

char u = Serial.read(); 
if(u=='1'){
  digitalWrite(L,HIGH);
}

else if(u=='0'){
digitalWrite(L,LOW);
  
}
}
