int AnalogPin = A0;    // Analog input
int DigitalPin = 7;  // Digital input
int LedPin = 13;     // select the pin for the LED
int gValue = 0;     // variable for Sensor Data

void setup (){
  pinMode (LedPin, OUTPUT);
  Serial.begin (9600);
}

void loop (){

  gValue = analogRead(AnalogPin);

  if (gValue>500) {digitalWrite (LedPin, HIGH);}
  else {digitalWrite (LedPin, LOW);}

  Serial.print ("Sensor Value : ");
  Serial.println (gValue, DEC);

  delay(500);

}