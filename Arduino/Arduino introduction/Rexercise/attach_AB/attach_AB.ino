const int AB = 10;
const int B = 2;

int BS = LOW;
bool BSC = false;

void BP() {

  BS = (BS == LOW) ? HIGH : LOW;
  BSC = true;
}

void setup() {

  pinMode(AB, OUTPUT);
  pinMode(B, INPUT);

  attachInterrupt(digitalPinToInterrupt(B), BP, RISING);

}

void loop() {

  if (BSC) {

    BSC = false;
    digitalWrite(AB, BS);
  }
}
