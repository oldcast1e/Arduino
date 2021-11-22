const int LED1  = 7;
const int LED2 = 5;

int ls = true;
int fadecnt = 0;
int fadeval = 0;

long blink_pvm = 0;
long fade_pvm = 0;

long blink_interval = 1000;
long fade_interval = 50;

void blink_fc() {
  unsigned long crmil = millis();
  if ((crmil - blink_pvm) >= blink_interval) {
    blink_pvm = crmil;
    digitalWrite(LED1, ls);
    ls = (ls == HIGH ? LOW : HIGH);
  }
}

void fade_fc() {

  unsigned crmil_ = millis();
  if (crmil_ - fade_pvm >= fade_interval) {
    fade_pvm = crmil_;

    if (fadecnt == 0) {
      if (fadeval < 255) fadeval += 5;
      if (fadeval == 255) fadecnt = 1;

    }
    else {
      if (fadeval > 0) fadeval -= 5;
      if (fadeval == 0) fadecnt = 0;
    }

  analogWrite(LED2,fadeval);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  blink_fc();
  fade_fc();



}
