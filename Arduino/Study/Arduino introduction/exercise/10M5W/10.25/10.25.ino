const int b = 10;
const int d[9] = {-1,262,294,330,349,393,440,494,523};

void setup() {

Serial.begin(115200);

}

void loop() {

if(Serial.available()){

  int k = Serial.read(); 
  if( '1' <= k && k <= '9'){
    int n = k - '0' ;

    tone(b,d[n]);
    delay(250);
  }

  
}

 noTone(b);
}
