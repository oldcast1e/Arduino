const int L = 12;
const int B = 2;

int LS = 0;
bool LSC = false;

void BP() {
  LS = (LS == LOW) ? HIGH : LOW;
  LSC = true;
}

void setup() {

  pinMode(L, OUTPUT);
  pinMode(B, INPUT);

  attachInterrupt(digitalPinToInterrupt(B), BP, RISING);
}

void loop() {

  if (LSC) {
    LSC = false;
    digitalWrite(L, LS);

  }
}
