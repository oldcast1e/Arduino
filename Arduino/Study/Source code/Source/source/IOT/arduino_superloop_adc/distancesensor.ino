int distancesensor_Pin = A3;    
int distancesensor_ledPin[3] = {10,9,6}; 
int distancesensor_Value = 0; 
int distancesensor_outputValue = 0;

long distancesensor_previousMillis = 0;
long distancesensor_interval = 1000;

void distancesensor_setup() { }

void distancesensor_loop() {
  unsigned long currentMillis = millis();
 
  if(currentMillis - distancesensor_previousMillis >= distancesensor_interval) { 
    distancesensor_previousMillis = currentMillis;   

    distancesensor_Value = analogRead(distancesensor_Pin);    
    distancesensor_outputValue = map(distancesensor_Value, 0, 1023, 0, 255);
    for(int i=0;i<3;i++)
      analogWrite(distancesensor_ledPin[i], distancesensor_outputValue);
    
    Serial.print("distancesensor value = " );
    Serial.print(distancesensor_Value);
    Serial.print(", led brightness = ");
    Serial.print(distancesensor_outputValue);
    
    float voltage = (distancesensor_Value/1024.0) * 5.0;  
    Serial.print(", volts = " );
    Serial.print(voltage);
    
    int distance = (6762/(distancesensor_Value-9))-4;
    Serial.print(", distance(cm) = " );
    Serial.println(distance);    
  }
}
