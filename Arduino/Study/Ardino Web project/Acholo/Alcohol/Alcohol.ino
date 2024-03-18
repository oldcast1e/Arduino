int mq3 = A7;
int red = 3;

void setup(){

    Serial.begin(9600);
    pinMode(red,OUTPUT);
    digitalWrite(red,LOW);
    
}

void loop(){
    int val = analogRead(mq3);
    Serial.println(val); delay(1000);
    if(val >=  400) digitalWrite(red,HIGH);

}
