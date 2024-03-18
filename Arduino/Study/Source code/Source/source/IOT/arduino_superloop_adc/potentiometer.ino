const int pot_analogInPin = A0;  
const int pot_analogOutPin = 11; 

int pot_sensorValue = 0;        
int pot_outputValue = 0;

long pot_previousMillis = 0;
long pot_interval = 2; 

void potentiometer_setup() {}

void potentiometer_loop() {
  unsigned long currentMillis = millis();
 
  if(currentMillis - pot_previousMillis >= pot_interval) { 
    pot_previousMillis = currentMillis;   

    pot_sensorValue = analogRead(pot_analogInPin);
    pot_outputValue = map(pot_sensorValue, 0, 1023, 0, 255);
    analogWrite(pot_analogOutPin, pot_outputValue);
    
    Serial.print("potentiometer value = " );
    Serial.print(pot_sensorValue);
    Serial.print(", led brightness = ");
    Serial.println(pot_outputValue);
  }
}
