int ledESP12 = D0; //16도 가능
int ledNodeMCU = D4; //2도 가능

void setup() { 

}

void loop() {
  for(int fadeValue=1023;fadeValue>=0;fadeValue--) {
	analogWrite(ledESP12, fadeValue);
	analogWrite(ledNodeMCU, fadeValue);
	delay(1);
  }
}