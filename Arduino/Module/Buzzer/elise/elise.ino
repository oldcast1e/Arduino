#define PIEZO 8 // 피에조 부저



// middle 도에서 부터 1 옥타브 음정과 주기값. 이 중에 우리가 쓸 것은 솔, 라, 미
#define c4 3822 // 261.63Hz 도
#define d4 3405 // 293.67Hz 레
#define e4 3034 // 329.63Hz 미
#define f4 2863 // 349.23Hz 파
#define g4 2551 // 392.11Hz 솔
#define g4s 2408 // 415.30Hz 솔#
#define a4 2273 // 440.11Hz 라
#define b4 2025 // 493.88Hz 시
#define c5 1910 // 523.25Hz 도
#define d5 1703 // 587.33Hz 레

#define d5s 1607 // 584.37Hz 레#
#define e5 1517 // 659.26Hz 미
#define f5 1432 // 698.46Hz 파
#define g5 1276 // 783.99Hz 솔
#define a5 1136 // 880.11Hz 라
#define b5 1012 // 987.77Hz 시



int song[] = { e5, d5s, e5, d5s, e5, b4, d5, c5, a4, c4, e4, a4, b4, e4, g4s, b4, c5, e4, e5, d5s, e5, d5s, e5, b4, d5, c5, a4, c4, e4, a4, b4, e4, c5, b4, a4 };



int song_pivot = 0;
unsigned long mil = 0;



void setup() {
  pinMode(PIEZO, OUTPUT);
}



void loop() {
  if (millis() - mil > 100) {
    int isLong;


    if(song_pivot == 8 || song_pivot == 12 || song_pivot == 16 || song_pivot == 26 || song_pivot == 30) {
      isLong = 3;
    } else if(song_pivot == 34) {
      isLong = 6;
    }


    sing(song[song_pivot++], isLong);
    if(song_pivot == 35)  song_pivot = 0;
    mil = millis();
  }
}



void sing(int eum, int isLong) {
  long lele = 125000;



  if(isLong == 3) lele = 375000;
  else if(isLong == 6) lele = 750000;



  for(long i=0; i< lele ; i+= eum) {
    digitalWrite(PIEZO, HIGH);
    delayMicroseconds(eum/2);
    digitalWrite(PIEZO, LOW);
    delayMicroseconds(eum/2);
  }
}

