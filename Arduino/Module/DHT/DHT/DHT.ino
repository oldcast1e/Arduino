#include<dht.h>
dht DHT;
#define DHT11_PIN 2
float hum; //Stores humidity value
float temp; //Stores temperature value

void setup() {
Serial.begin(9600);
}

void loop() {
DHT.read11(DHT11_PIN);
hum = DHT.humidity;
temp = DHT.temperature;

Serial.print("Humidity: ");
Serial.print(hum);
Serial.print(" %, Temp: ");
Serial.print(temp);
Serial.println(" Celsius");
delay(100); //Delay 2 sec.
}
