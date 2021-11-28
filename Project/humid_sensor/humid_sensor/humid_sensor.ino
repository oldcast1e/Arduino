//dht 외부 library 필요!!
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN,DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("humidity: ");

  Serial.println(h);
  Serial.print("temperature: ");

  Serial.println(t);
  delay(1000);
  
}
/*
 * humidity:56.60 (10~14)
   temperature:24.70(13~17)

 */
