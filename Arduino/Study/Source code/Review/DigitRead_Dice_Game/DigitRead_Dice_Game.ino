const int led[6] = {3, 4, 5, 6, 7, 8};
const int b = 10;

int cnt = 0;
void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 6; i++) pinMode(led[i], OUTPUT);
  Serial.begin(115200);
  pinMode(b, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int n = digitalRead(b);

  if (n == 1) {
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 6; j++)digitalWrite(led[j], LOW);

      digitalWrite(led[i], HIGH);
      delay(50);
      if (digitalRead(b) == 0){
        Serial.print("The Number You chose: ");
        Serial.println(i+1);
        break;
      }

    }

  }
  //  while(n==1){
  //    for(int i=0;i<6;i++){
  //
  //      if(n==0) break;
  //
  //      if(i==0){
  //        digitalWrite(led[5],LOW);
  //        digitalWrite(led[0],HIGH);
  //        Serial.println(n);
  //        delay(500);
  //      }
  //      else{
  //        digitalWrite(led[i-1],LOW);
  //        digitalWrite(led[i],HIGH);
  //        Serial.println(n);
  //        delay(500);
  //      }
  //    }
  //  }

}
