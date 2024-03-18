const int L[7] = {2, 3, 4, 5, 6, 7, 8};

const int N[10][7] = {

  {1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 0, 1},
  {1, 1, 1, 1, 0, 0, 1},
  {0, 1, 1, 0, 0, 1, 1},
  {1, 0, 1, 1, 0, 1, 1},
  {1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 1, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1}

};

void DC() {

  for (int n = 0; n < 7; n++) {
    digitalWrite(L[n], LOW);
  }

}

void NF(int n) {

  if (0 <= n && n <= 9) {

    for (int x = 0; x <= 9; x++) {
      digitalWrite(L[x], N[n][x] == 1 ? HIGH : LOW);
    }
  }
}

void setup() {

  for (int n = 0; n < 7; n++) {
    pinMode(L[n], OUTPUT);
  }

  DC();

  Serial.begin(9600);
}


void loop() {

  if(Serial.available()){

    char u = Serial.read();

    if( '0' <= u && u <= '9'){
    int num = u -'0';
    DC();
    NF(num);
    }
  }

}
