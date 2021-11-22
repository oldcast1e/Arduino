unsigned const int L[7] = {2, 3, 4, 5, 6, 7, 8};

void setup() {

  for (int x = 0; x <= 6; x++) {

    pinMode(L[x], OUTPUT);
  }

 
}
void loop() {

for (int x = 0; x <= 5; x++) {

  for(int y=0; y<=5;y++){
    digitalWrite(L[y],LOW);
  }

    digitalWrite(L[x], HIGH); 
    delay(100);
}
}
