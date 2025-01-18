// C++ code
//
#define LED_1 5
#define LED_2 6
#define key_1 2

void setup()
{
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(key_1, INPUT);
  
}

void loop(){
  if(digitalRead(key_1) == HIGH){
    for (int i = 0; i < 8; i++){
       digitalWrite(LED_1, HIGH);   
       delay(200);
       digitalWrite(LED_1, LOW);   
       delay(200);
    }
    digitalWrite(LED_1, HIGH);    
  }
  else {
    digitalWrite(LED_1, LOW);    
    while(1){
      if(digitalRead(key_1) == HIGH) break;
      digitalWrite(LED_2, HIGH);   
       delay(200);
       digitalWrite(LED_2, LOW);   
       delay(200);
    }
  }

}