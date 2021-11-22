const int LED = 13;
//아두이노 기본 LED
void setup()
{
  Serial.begin(9600);

  pinMode(LED,OUTPUT);
}

void loop()
{
  if(Serial.available()>0){
    char u = Serial.read();
    if(u == 1) digitalWrite(LED,HIGH);
    else  digitalWrite(LED,LOW);
    
  }
  
}
