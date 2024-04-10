#include <math.h>
int sensorPin = A0; // Declaration of the input pin
// These function translates the recorded analog measurement
double Thermistor(int RawADC)
{
 double Temp;
 Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
 Temp = 1 /(0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp)) * Temp);
 Temp = Temp - 273.15; // convert from Kelvin to Celsius
 return Temp;
}

void setup(){
  Serial.begin(9600);
}
void loop()
{
 int readVal = analogRead(sensorPin);
 double temp = Thermistor(readVal);
 // Output on the serial interface
 Serial.print("Current temperature is:");
 Serial.print(temp);
 Serial.print("°");
// Serial.print(char(186)); //Output <°> Symbol
 Serial.println("C");
 Serial.println("---------------------------------------");
 delay(500);
}
