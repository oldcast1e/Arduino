//하울의 움직이는 성 ost

char piano = 8;

float A[] = {27.5, 55, 110, 220, 440, 880, 1760, 3520};
float As[] = {29.1, 58.3, 116.5, 233.1, 446.2, 932.3, 1864.7, 3729.3};
float B[] = {30.9, 61.7, 123.5, 246.9, 493.9, 987.8, 1975.5, 3951.1};
float C[] = {32.7, 65.4, 130.8, 261.6, 523.3, 1046.5, 2093, 4186};
float Cs[] = {34.6, 69.3, 139.6, 277.2, 544.4, 1108.7, 2217.5};
float D[] = {36.7, 73.4, 146.8, 293.7, 587.3, 1174.7, 2349.3};
float Ds[] = {38.9, 77.8, 155.6, 311.1, 622.3, 1244.5, 2489};
float E[] = {41.2, 82.4, 164.8, 329.6, 659.3, 1318.5, 2637};
float F[] = {43.7, 87.3, 174.6, 349.2, 698.5, 1396.9, 2793.8};
float Fs[] = {46.2, 92.5, 185, 370, 740, 1480, 2960};
float G[] = {49, 98, 196, 392, 780, 1568, 3136};
float Gs[] = {51.9, 103.8, 207.7, 415.3, 830, 1661.2, 3322.4};

void setup() {
 pinMode(piano, OUTPUT);
 
    tone(piano, D[4]);delay(500);
    tone(piano, G[4]);delay(500);
    tone(piano, As[5]);delay(500);
    tone(piano, D[5]);delay(700);
    noTone(piano);delay(400);
 
    tone(piano, D[5]);delay(500);
    tone(piano, C[5]);delay(500);
    tone(piano, As[5]);delay(500);
    tone(piano, A[5]);delay(500);
    tone(piano, As[5]);delay(900);
    noTone(piano);delay(400);
 
    tone(piano, G[4]);delay(500);
    tone(piano, As[5]);delay(500);
    tone(piano, D[5]);delay(500);
    tone(piano, G[5]);delay(700);
    noTone(piano);delay(400);
 
    tone(piano, G[5]);delay(500);
    noTone(piano);delay(10);
    tone(piano, G[5]);delay(500);
    tone(piano, A[6]);delay(400);
    tone(piano, F[5]);delay(300);
    tone(piano, Ds[5]);delay(300);
    tone(piano, F[5]);delay(1000);
    noTone(piano);delay(400);

    tone(piano, As[5]);delay(500);
    tone(piano, D[5]);delay(500);
    tone(piano, F[5]);delay(500);
    tone(piano, A[6]);delay(1000);
    tone(piano, G[5]);delay(500);
    tone(piano, F[5]);delay(500);
    tone(piano, E[5]);delay(500);
    tone(piano, F[5]);delay(500);
    tone(piano, G[5]);delay(1000);
    tone(piano, F[5]);delay(500);
    tone(piano, E[5]);delay(1000);
    tone(piano, D[5]);delay(500);
    tone(piano, C[5]);delay(500);
    tone(piano, As[5]);delay(500);
    tone(piano, C[5]);delay(500);
    tone(piano, D[5]);delay(500);
    tone(piano, C[5]);delay(500);
    tone(piano, G[4]);delay(500);
    tone(piano, A[5]);delay(1000);
    noTone(piano);delay(400);

    tone(piano, As[5]);delay(1000);
    tone(piano, A[5]);delay(1000);
    tone(piano, C[5]);delay(150);
    tone(piano, As[5]);delay(1000);
    tone(piano, A[5]);delay(1000);
    noTone(piano);delay(400);
 
    tone(piano, A[4]);delay(550);
    tone(piano, D[4]);delay(500);
    noTone(piano);delay(10);
    tone(piano, D[4]);delay(500);
    noTone(piano);delay(10);

    tone(piano, A[4]);delay(550);
    tone(piano, D[4]);delay(500);
    noTone(piano);delay(10);
    tone(piano, D[4]);delay(500);
    noTone(piano);delay(10);
 
    tone(piano, A[4]);delay(550);
    tone(piano, D[4]);delay(500);
    noTone(piano);delay(10);
    tone(piano, D[4]);delay(500);
    noTone(piano);delay(10);

    tone(piano, D[4]);delay(500);
    tone(piano, G[4]);delay(500);
    tone(piano, As[5]);delay(500);
    tone(piano, D[5]);delay(700);
    noTone(piano);delay(400);
 
    tone(piano, D[5]);delay(500);
    tone(piano, C[5]);delay(500);
    tone(piano, As[5]);delay(500);
    tone(piano, A[5]);delay(500);
    tone(piano, As[5]);delay(900);
    noTone(piano);delay(400);

    tone(piano, G[4]);delay(500);
    tone(piano, As[5]);delay(500);
    tone(piano, D[5]);delay(500);
    tone(piano, G[5]);delay(700);
    noTone(piano);delay(400);
 
    tone(piano, G[5]);delay(500);
    noTone(piano);delay(10);
    tone(piano, G[5]);delay(500);
    tone(piano, A[6]);delay(400);
    tone(piano, F[5]);delay(300);
    tone(piano, Ds[5]);delay(300);
    tone(piano, F[5]);delay(1000);
    noTone(piano);delay(400);

    tone(piano, As[5]);delay(500);
    tone(piano, D[5]);delay(500);
    tone(piano, F[5]);delay(500);
    tone(piano, A[6]);delay(1000);
    tone(piano, G[5]);delay(500);
    tone(piano, F[5]);delay(300);
    tone(piano, E[5]);delay(300);
    tone(piano, D[5]);delay(300);
    tone(piano, E[5]);delay(300);
    tone(piano, G[5]);delay(1000);
    tone(piano, F[5]);delay(500);
    tone(piano, E[5]);delay(300);
    tone(piano, D[5]);delay(300);
    tone(piano, C[5]);delay(300);
    tone(piano, D[5]);delay(300);
    noTone(piano);delay(10);
 
    tone(piano, D[5]);delay(500);
    tone(piano, C[5]);delay(300);
    tone(piano, D[5]);delay(300);
    tone(piano, C[5]);delay(300);
    tone(piano, As[5]);delay(300);
    tone(piano, A[5]);delay(700);
    tone(piano, B[5]);delay(300);
    tone(piano, Cs[5]);delay(500);
    tone(piano, D[5]);delay(1000);
    noTone(piano);delay(10);
 
 
    tone(piano, D[5]);delay(500);
    tone(piano, Ds[5]);delay(1000);
    tone(piano, D[5]);delay(500);
    tone(piano, C[5]);delay(500);
    tone(piano, As[5]);delay(500);
    tone(piano, A[5]);delay(500);
    tone(piano, As[5]);delay(500);
    tone(piano, C[5]);delay(500);
    tone(piano, D[5]);delay(500);
 
    tone(piano, F[4]);delay(1000);
    noTone(piano);delay(10);
    tone(piano, F[4]);delay(500);
    tone(piano, Ds[5]);delay(1000);
    tone(piano, D[5]);delay(500);
    tone(piano, C[5]);delay(1000);
    tone(piano, As[5]);delay(300);
    tone(piano, C[5]);delay(500);
    tone(piano, D[5]);delay(1000);
    noTone(piano);delay(10);
    tone(piano, D[5]);delay(300);
    noTone(piano);delay(10);
    tone(piano, D[5]);delay(300);
 
    tone(piano, Cs[5]);delay(500);
    tone(piano, D[5]);delay(500);
    tone(piano, F[5]);delay(500);
    tone(piano, E[5]);delay(500);
    tone(piano, D[5]);delay(500);
    tone(piano, Cs[5]);delay(1000);
    tone(piano, E[5]);delay(500);
    tone(piano, A[5]);delay(1000);
    noTone(piano);delay(10);
    tone(piano, A[5]);delay(500);
    tone(piano, F[5]);delay(1000);
    noTone(piano);delay(10);
    tone(piano, F[5]);delay(500);
    noTone(piano);delay(10);
    tone(piano, F[5]);delay(500);
    tone(piano, E[5]);delay(500);
    tone(piano, D[5]);delay(500);
    tone(piano, E[5]);delay(2000);
 
    tone(piano, Fs[5]);delay(1000);
    noTone(piano);delay(10);
    tone(piano, Fs[5]);delay(500);
    noTone(piano);delay(10);
    tone(piano, Fs[5]);delay(500);
    tone(piano, G[5]);delay(500);
    tone(piano, A[6]);delay(500);
    tone(piano, As[6]);delay(2000);

    tone(piano, E[5]);delay(1000);
    noTone(piano);delay(10);
    tone(piano, E[5]);delay(500);
    noTone(piano);delay(10);
    tone(piano, E[5]);delay(500);
    tone(piano, F[5]);delay(500);
    tone(piano, G[5]);delay(500);
    tone(piano, A[6]);delay(2000);
 
    tone(piano, D[5]);delay(500);
    noTone(piano);delay(10);
    tone(piano, D[5]);delay(500);
    noTone(piano);delay(10);
    tone(piano, D[5]);delay(500);
    tone(piano, Cs[5]);delay(500);
    tone(piano, D[5]);delay(500);

    tone(piano, Cs[5]);delay(1000);
    tone(piano, E[5]);delay(500);
    tone(piano, A[6]);delay(1000);
    tone(piano, G[5]);delay(500);
    tone(piano, Fs[5]);delay(2000);

    tone(piano, D[4]);delay(500);
    tone(piano, G[4]);delay(500);
    tone(piano, As[5]);delay(500);
    tone(piano, D[5]);delay(700);
    noTone(piano);delay(400);
 
    tone(piano, D[5]);delay(500);
    tone(piano, C[5]);delay(500);
    tone(piano, As[5]);delay(500);
    tone(piano, A[5]);delay(500);
    tone(piano, As[5]);delay(700);
    noTone(piano);delay(400);
 
    tone(piano, G[4]);delay(500);
    tone(piano, As[5]);delay(500);
    tone(piano, D[5]);delay(500);
    tone(piano, G[5]);delay(700);
    noTone(piano);delay(400);
 
    tone(piano, G[5]);delay(500);
    noTone(piano);delay(10);
    tone(piano, G[5]);delay(500);
    tone(piano, A[6]);delay(400);
    tone(piano, F[5]);delay(300);
    tone(piano, Ds[5]);delay(300);
    tone(piano, F[5]);delay(1000);
    noTone(piano);delay(400);

    tone(piano, As[5]);delay(500);
    tone(piano, D[5]);delay(500);
    tone(piano, F[5]);delay(500);
    tone(piano, A[6]);delay(1000);
    tone(piano, G[5]);delay(500);
    tone(piano, F[5]);delay(300);
    tone(piano, E[5]);delay(300);
    tone(piano, D[5]);delay(300);
    tone(piano, E[5]);delay(300);
    tone(piano, G[5]);delay(1000);
    tone(piano, F[5]);delay(500);
    tone(piano, E[5]);delay(300);
    tone(piano, D[5]);delay(300);
    tone(piano, C[5]);delay(300);
    tone(piano, D[5]);delay(300);
    noTone(piano);delay(10);
 
    tone(piano, D[5]);delay(500);
    tone(piano, C[5]);delay(300);
    tone(piano, D[5]);delay(300);
    tone(piano, C[5]);delay(300);
    tone(piano, As[5]);delay(300);
    tone(piano, A[5]);delay(1000);
    tone(piano, B[5]);delay(300);
    tone(piano, Cs[5]);delay(500);
    tone(piano, D[5]);delay(1000);
    noTone(piano);delay(10);
 
    tone(piano, D[4]);delay(300);
    noTone(piano);delay(10);
    tone(piano, D[4]);delay(500);
    tone(piano, C[4]);delay(300);
    tone(piano, D[4]);delay(300);
    tone(piano, C[4]);delay(300);
    tone(piano, As[4]);delay(300);
    tone(piano, A[4]);delay(1000);
    tone(piano, B[4]);delay(300);
    tone(piano, Cs[4]);delay(500);
    tone(piano, D[4]);delay(1500);
    noTone(piano);delay(10000);
 
}
void loop() {
 
}