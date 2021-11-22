const int B = 2;
const int b = 10;//부져

const int melody[24] {
  392, 392, 440, 440, 392, 392, 329, 392, 392, 329, 329, 293, 392, 392, 440, 440, 392, 392, 329, 392, 329, 293, 329, 261,
};

int BS = LOW;
bool BSC = false;

void S() {

  for (int n = 0; n <= 23; n++) {
    tone(b, melody[n]);
    delay(50);
  }
}

void BP() {

  BS = (BS == LOW) ? HIGH : LOW;
  BSC = true;
}

void setup() {

  pinMode(B, INPUT);
  pinMode(b, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(B), BP, RISING);
}

void loop(){

if(BSC){
  BSC = false;
  S();
}
}
