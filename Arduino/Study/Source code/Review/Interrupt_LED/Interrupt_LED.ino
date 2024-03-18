const int LED  = 3;
const int bt = 2;

int ls = LOW;
bool lsc = false;

void bf(){
  ls = (ls==HIGH?LOW:HIGH);
  lsc  = true;  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  pinMode(bt,INPUT);
  attachInterrupt(digitalPinToInterrupt(bt),bf,RISING);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(lsc){
    digitalWrite(LED,ls);
    lsc = false;
  }

}
