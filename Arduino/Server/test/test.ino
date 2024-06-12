#include <LCDWIKI_GUI.h> // 기본 그래픽 라이브러리 포함
#include <LCDWIKI_KBV.h> // 하드웨어 특화 라이브러리 포함

// IC 모델이 알려져 있거나 모듈을 읽을 수 없는 경우 사용할 수 있는 생성자 함수
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4); // 모델, cs, cd, wr, rd, reset 핀 설정

// 일부 색상 값 정의
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup() {
  Serial.begin(115200);   // 시리얼 모니터 포트 초기화
  Serial1.begin(115200);  // Serial1 포트 초기화
  Serial.write("Arduino Mega Serial1 test - for loopback test connect pin 18 to pin 19\n"); // 시리얼 모니터에 테스트 메시지 출력

  // LCD 초기화
  mylcd.Init_LCD();
  Serial.println(mylcd.Read_ID(), HEX); // LCD ID를 시리얼 모니터에 출력
  mylcd.Fill_Screen(WHITE); // 화면을 흰색으로 채움
  mylcd.Set_Text_Mode(0); // 텍스트 모드 설정
  mylcd.Set_Text_Back_colour(WHITE); // 배경 색상을 흰색으로 설정
  mylcd.Set_Text_Size(3); // 텍스트 크기를 3으로 설정
  mylcd.Set_Rotation(3); // 화면 회전을 가로 모드로 설정
}

void loop() {
  if (Serial1.available()) { // Serial1에 데이터가 있으면
    String inputString = Serial1.readString(); // Serial1로부터 문자열을 읽음
    inputString.trim(); // 문자열의 앞뒤 공백을 제거

    Serial.print("inputString: "); Serial.println(inputString); // 읽은 문자열을 시리얼 모니터에 출력

    mylcd.Fill_Screen(WHITE); // 새 데이터가 수신되면 화면을 흰색으로 채움
    mylcd.Set_Text_colour(BLACK); // 텍스트 색상을 검정색으로 설정
    printMultilineString(inputString); // 줄바꿈 처리된 문자열을 출력
  }

  if (Serial.available()) { // Serial에 데이터가 있으면
    int inByte = Serial.read(); // Serial로부터 바이트를 읽음
    Serial1.write(inByte); // 읽은 바이트를 Serial1로 전송
  }
}

void printMultilineString(String str) {
  int yOffset = 0; // 시작 y 위치
  int lineHeight = 15; // 한 줄의 높이, 텍스트 크기에 맞게 조정
  bool isRed = true; // 색상 상태를 체크하는 플래그
  bool isBus = false; // 색상 상태를 체크하는 플래그

  while (str.length() > 0) { // 문자열 길이가 0보다 큰 동안 반복
    int newlineIndex = str.indexOf('\n'); // '!' 문자의 인덱스를 찾음
    String line;
    if (newlineIndex == -1) { // '!' 문자가 없으면
      line = str; // 전체 문자열을 한 줄로 설정
      str = ""; // 남은 문자열을 빈 문자열로 설정
    } else {
      line = str.substring(0, newlineIndex); // '!' 이전의 문자열을 한 줄로 설정
      str = str.substring(newlineIndex + 1); // '!' 이후의 문자열로 설정
    }

    for (int i = 0; i < line.length(); i++) { // 한 줄의 각 문자를 처리
      if (line[i] == '.') {isRed = false; isBus = true;} // '.' 문자가 있으면 isRed를 false로, isBus를 true로 설정
      else if (line[i] == ':' && !isRed) isBus = false; // ':' 문자가 있고 isRed가 false이면 isBus를 false로 설정
      
      if (isRed) {mylcd.Set_Text_colour(RED);} // isRed가 true이면 텍스트 색상을 빨간색으로 설정
      else if (isBus) {mylcd.Set_Text_colour(BLUE);} // isBus가 true이면 텍스트 색상을 파란색으로 설정
      else {mylcd.Set_Text_colour(BLACK);} // 그렇지 않으면 텍스트 색상을 검정색으로 설정

      char c = line[i]; // 현재 문자를 가져옴
      if (c != '.') mylcd.Print_String(String(c).c_str(), i*20 , yOffset); // 문자가 '.'이 아니면 해당 문자를 출력, x 위치는 문자 순서에 따라 조정
    }
    yOffset += lineHeight; // 다음 줄로 이동
  }
}
