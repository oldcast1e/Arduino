#include <SPI.h>
#include <SD.h>
#include <LCDWIKI_GUI.h>   // Core graphics library
#include <LCDWIKI_KBV.h>   // Hardware-specific library

// LCD 설정
#define LCD_CS 9   // 디스플레이 Chip Select 핀 (적절히 설정 필요)
#define LCD_RST 8  // 디스플레이 Reset 핀
#define LCD_DC 7   // 디스플레이 Data/Command 핀

// Define color values
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// SD 카드 설정
#define SD_CS 10   // SD 카드 Chip Select 핀

// LCD 객체 생성
LCDWIKI_KBV mylcd(ILI9486, LCD_CS, LCD_DC, A1, A0, LCD_RST);

void setup() {
  // 시리얼 통신 초기화
  Serial.begin(9600);
  Serial.println("Initializing...");

  // LCD 초기화
  Serial.println("Initializing LCD...");
  pinMode(LCD_CS, OUTPUT);
  digitalWrite(LCD_CS, LOW);  // LCD 활성화
  mylcd.Init_LCD();
  mylcd.Fill_Screen(BLACK);
  digitalWrite(LCD_CS, HIGH); // LCD 비활성화

  // SD 카드 초기화
  Serial.println("Initializing SD card...");
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, LOW);   // SD 카드 활성화
  if (!SD.begin(SD_CS)) {
    Serial.println("SD initialization failed!");
    Serial.println("Check wiring, card insertion, or format (FAT16/FAT32).");
    while (1);  // 초기화 실패 시 멈춤
  }
  Serial.println("SD card initialized successfully!");
  digitalWrite(SD_CS, HIGH);  // SD 카드 비활성화

  // 테스트 파일 생성 및 읽기
  testSDCard();
}

void loop() {
  // 메인 루프에서 아무 동작도 하지 않음
}

void testSDCard() {
  // SD 카드 테스트: 파일 생성 및 읽기
  Serial.println("Testing SD card...");
  digitalWrite(SD_CS, LOW);  // SD 카드 활성화

  // 파일 생성 및 쓰기
  File testFile = SD.open("test.txt", FILE_WRITE);
  if (testFile) {
    Serial.println("Writing to test.txt...");
    testFile.println("Hello, SD card!");
    testFile.close();
    Serial.println("Write successful.");
  } else {
    Serial.println("Failed to open test.txt for writing.");
  }

  // 파일 읽기
  testFile = SD.open("test.txt");
  if (testFile) {
    Serial.println("Reading from test.txt:");
    while (testFile.available()) {
      Serial.write(testFile.read());
    }
    testFile.close();
    Serial.println("\nRead successful.");
  } else {
    Serial.println("Failed to open test.txt for reading.");
  }

  digitalWrite(SD_CS, HIGH);  // SD 카드 비활성화
}

