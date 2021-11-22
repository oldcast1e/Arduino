//const int L2 = 2;
//const int b2 = 22;
//int fadingstate = 0;
//long fdpm = 0;
//long fddt = 1000;
//
//void fading_setup(){
//
//  pinMode(L2,OUTPUT);
//  pinMode(b2,INPUT);
//}
//
//void fading_loop(){
//
//  long fdn = millis();
//  
//  if(fdn - fdpm>=fddt){
//
//    if(fadingstate==0){
//      for(int n =0;n<=255;n++){
//        analogWrite(L2,n);
//        if(n==255){
//          fadingstate = 1;
//        }
//      }
//    }
//
//    else if(fadingstate==1){
//      for(int n =255;n>=0;n--){
//        analogWrite(L2,n);
//        if(n==0){
//          fadingstate = 0;
//        }
//      }
//    }
//  }
//}
