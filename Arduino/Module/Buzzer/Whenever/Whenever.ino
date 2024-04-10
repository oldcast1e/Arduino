int speakerpin = 8;
int doo = 261;
int le = 293;
int me = 329;
int fa = 349;
int sol= 391;
int la = 440;
int si = 493;
int highdo = 523;
int highle = 587;
int highme = 659;
int lashap = 466;
void setup() {
  // put your setup code here, to run once:
  sound(fa,500);
  sound(sol,500);

  soundf(250);
  sound(fa,250);
  sound(highdo,750);
  sound(la,250);

  soundc(500);
  sound(highdo,500);
  sound(sol,500);

  sounddm(250);
  sound(le,250);
  sound(la,750);
  sound(fa,250);

  //2번째 줄 
  soundam(1000);
  sound(me,500);

  soundbb(500);
  sound(me,500);
  sound(fa,250);
  sound(sol,250);

  soundf2(500);
  sound(fa,500);
  sound(sol,250);
  sound(la,250);


  //세번째 줄 
  soundgm7(500);
  sound(lashap,250);
  sound(la,250);
  sound(sol,250);
  sound(fa,250);

  soundc(500);
  sound(doo,500);
  sound(fa,250);
  sound(sol,250);

  soundf(1000);
  delay(10);
  sound(doo,500);
  delay(10);

  soundf(1000);
  delay(10);
  sound(la,250);
  sound(lashap,250);

    //네번째 줄 
  soundf3(500);
  delay(10);
  sound(highdo,500);
  sound(highdo,500);

  soundc2(500);
  delay(10);
  sound(highdo,250);
  sound(highle,250);
  sound(highdo,250);
  sound(lashap,250);

  sounddm2(500);
  delay(10);
  sound(la,500);
  sound(la,500);

  soundam2(500);
  delay(10);//알수없는 에러 딜레이로 고치기 
  sound(la,250);
  sound(lashap,250);
  sound(la,250);
  sound(sol,250);
  //다섯번재줄
  sounddm(500);
  delay(10);
  sound(fa,500);
  sound(fa,250);
  sound(me,250);

  soundbb(500);
  delay(10);
  sound(me,500);
  sound(me,250);
  sound(fa,250);

  soundgm(500);
  delay(10);
  sound(sol,250);
  sound(la,250);
  sound(sol,250);
  sound(la,250);

  soundc(500);
  delay(10);
  sound(doo,500);
  sound(la,250);
  delay(10);
  sound(lashap,250);
  
  //여섯번째줄
  soundf3(500);
  delay(10);
  sound(highdo,500);
  sound(highdo,500);

  soundc2(500);
  delay(10);
  sound(highdo,250);
  sound(highle,250);
  sound(highdo,250);
  sound(lashap,250);

  sounddm2(500);
  delay(10);
  sound(la,500);
  sound(la,500);


  //일곱번째줄
  soundam2(250);
  delay(10);
  sound(la,250);
  delay(10);
  sound(lashap,250);
  delay(10);
  sound(sol,250);
  sound(fa,250);
  sound(me,250);


  soundbb(500);
  delay(10);
  sound(le,250);
  sound(me,250);
  sound(fa,250);
  sound(sol,250);

  soundf2(500);
  delay(10);
  sound(fa,500);
  sound(sol,250);
  sound(la,250);

  
  //여덜번째줄
  soundc(750);
  delay(10);
  sound(sol,250);
  sound(sol,250);
  sound(fa,250);

  soundf(1000);
  delay(10);
  sound(doo,500);

  soundf(1000);
  delay(10);
  sound(fa,250);
  sound(sol,250);
  
  //아홉번째줄
  soundbb(500);
  delay(10);
  sound(me,500);
  sound(fa,250);
  sound(sol,250);

  soundf2(500);
  delay(10);
  sound(fa,750);
  sound(me,250);

  soundbb(500);
  delay(10);
  sound(me,500);
  sound(fa,250);
  sound(sol,250);

  soundf2(1000);
  delay(10);
  sound(fa,250);
  sound(me,250);
  //10번째줄 
   soundbb(500);
   delay(10);
  sound(me,500);
  sound(fa,250);
  sound(sol,250);

  soundf2(500);
  delay(10);
  sound(fa,500);
  sound(sol,250);
  sound(la,250);

  soundgm7(500);
  delay(10);
  sound(lashap,250);
  sound(la,250);
  soundc(250);
  sound(fa,250);

  soundf(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
void sound(int name,int time)
{
  tone(speakerpin,name,time);
  delay(time+1);
 
}
void soundf(int time)
{
  tone(speakerpin,la,time);
  tone(speakerpin,fa,time);
  tone(speakerpin,doo,time);
  tone(speakerpin,la,time);
  delay(time);
}
void sounddm(int time)
{
  tone(speakerpin,fa,time);
  tone(speakerpin,le,time);
  tone(speakerpin,la,time);
  delay(time);
}
void soundam(int time)
{
  tone(speakerpin,me,time);
  tone(speakerpin,doo,time);
  tone(speakerpin,la,time);
  delay(time);
}
void soundc(int time)
{
  tone(speakerpin,sol,time);
  tone(speakerpin,doo,time);
  tone(speakerpin,sol,time);
  delay(time);
}
void soundbb(int time)
{
  tone(speakerpin,le,time);
  tone(speakerpin,lashap,time);
  delay(time);
}
void soundf2(int time)
{
  tone(speakerpin,doo,time);
  tone(speakerpin,la,time);
  delay(time);
}
void soundgm7(int time)
{
  tone(speakerpin,lashap,time);
  tone(speakerpin,fa,time);
  tone(speakerpin,doo,time);
  tone(speakerpin,sol,time);
  delay(time);
}
void soundc2(int time)
{
  tone(speakerpin,highdo,time);
  tone(speakerpin,me,time);
  tone(speakerpin,doo,time);
  tone(speakerpin,sol,time);
  delay(time);

}
void sounddm2(int time)
{
  tone(speakerpin,la,time);
   tone(speakerpin,fa,time);
  tone(speakerpin,le,time);
  tone(speakerpin,la,time);
  delay(time);
}
void soundam2(int time)
{
  tone(speakerpin,la,time);
  tone(speakerpin,me,time);
  tone(speakerpin,doo,time);
  tone(speakerpin,la,time);
  delay(time);
}
void soundgm(int time)
{
  tone(speakerpin,sol,time);
  tone(speakerpin,le,time);
  tone(speakerpin,la,time);
  delay(time);
}
void soundf3(int time)
{
  tone(speakerpin,highdo,time);
  tone(speakerpin,fa,time);
  tone(speakerpin,doo,time);
  tone(speakerpin,la,time);
  delay(time);
}