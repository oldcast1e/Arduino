int pin = 11;
volatile int state = LOW;

void setup() {
  pinMode(pin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), buttonIsr, RISING);
}

void loop() {
  digitalWrite(pin, state);
}

void buttonIsr() {
  state = !state;
}