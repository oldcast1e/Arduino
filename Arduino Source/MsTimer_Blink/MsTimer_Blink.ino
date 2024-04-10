void blink() {
  static boolean output = HIGH;
  digitalWrite(13, output); output = !output;
}
void setup() {
  pinMode(13, OUTPUT);
  MsTimer2::set(500, blink); MsTimer2::start();
}
void loop() { }
