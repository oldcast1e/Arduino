const int B = D3;

void setup(){

  Serial.begin(115200);
  pinMode(B,INPUT);
}
void loop(){  

   int u = digitalRead(B);
   Serial.println(u);

   
  
}
