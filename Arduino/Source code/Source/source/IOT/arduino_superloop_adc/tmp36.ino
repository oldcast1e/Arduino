int tmp36sensorPin = A1;
int tmp36ledPin = 13; 
int tmp36sensorValue = 0;

long tmp36_previousMillis = 0;
long tmp36_interval = 0;

int tmp36sensor_ledState = 1;

void tmp36sensor_setup() {  
  pinMode(tmp36ledPin, OUTPUT);  
}

void tmp36sensor_loop() {
  unsigned long currentMillis = millis();
 
  if(currentMillis - tmp36_previousMillis >= tmp36_interval) { 
    tmp36_previousMillis = currentMillis;   

    if(tmp36sensor_ledState != 0) {
      tmp36sensorValue = analogRead(tmp36sensorPin);
      tmp36_interval = tmp36sensorValue;
            
      Serial.print("temperature sensor value = " ); 
      Serial.print(tmp36sensorValue);
      
      float voltage = (tmp36sensorValue/1024.0) * 5.0;   
      Serial.print(", volts = " );
      Serial.print(voltage);
      
      float temperature = (voltage - .5) * 100;    
      Serial.print(", degrees C = " );
      Serial.println(temperature);
    }
    
    digitalWrite(tmp36ledPin, tmp36sensor_ledState);
    tmp36sensor_ledState = !tmp36sensor_ledState; 
  }
}
