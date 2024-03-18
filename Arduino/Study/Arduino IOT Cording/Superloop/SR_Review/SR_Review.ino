#define Serial Serial1

int bli =1;
int fad = 1; 

void setup() {
  // put your setup code here, to run once:
  blink_setup();
  fading_setup();
  RGB_setup();
  RGB_fading_setup();

  menu_setup();

}

void loop() {
  // put your main code here, to run repeatedly:
  menu_loop();
}
