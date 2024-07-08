#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

unsigned long lastActionTime = 0;  // 마지막 액션 시간 기록



void ServoAngleZero(){
    servo1.write(0); // 약지
    servo2.write(0); // 엄지
    servo3.write(0); // 검지
    servo4.write(0);  // 중지
    servo5.write(0); // 링
}

void ServoAngleOpen(){
    servo1.write(90); // 약지
    servo2.write(90); // 엄지
    servo3.write(90); // 검지
    servo4.write(90);  // 중지
    servo5.write(90); // 링
}

void UpThumb(){servo2.write(90);} // 엄지
void UpIndex(){servo3.write(90);} // 검지
void UpMiddle(){servo4.write(90);} // 중지
void UpRing(){servo5.write(90);} // 약지
void UpPinky(){servo1.write(90);} // 소지

void DownThumb(){servo2.write(0);} // 엄지
void DownIndex(){servo3.write(0);} // 검지
void DownMiddle(){servo4.write(0);} // 중지
void DownRing(){servo5.write(0);} // 약지
void DownPinky(){servo1.write(0);} // 소지

// void raiseThumb(){servo2.write(90);} // 엄지
void setup() {
    
    servo1.attach(8);servo2.attach(9);servo3.attach(10);servo4.attach(11);servo5.attach(12);

    // ServoAngleZero();// 손을 쥠
    ServoAngleOpen(); // 손을 핌

    DownRing(); // 검지 굽히기
    delay(1000);
    UpRing();
}

void loop() {
  //servo4.write(0);
  //delay(1500);
  //servo4.write(180);
}
