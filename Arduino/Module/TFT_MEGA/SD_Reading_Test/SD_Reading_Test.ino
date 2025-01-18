#include <SdFat.h>
#include <LCDWIKI_GUI.h>  // Core graphics library
#include <LCDWIKI_KBV.h>  // Hardware-specific library

// 핀 정의
#define SD_CS 10      // SD 카드 Chip Select 핀
#define LCD_CS 9      // 디스플레이 Chip Select 핀
#define LCD_RST 8     // 디스플레이 Reset 핀
#define LCD_DC 7      // 디스플레이 Data/Command 핀

// Define color values
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// SPI 속도 설정
#define SPI_SPEED SD_SCK_MHZ(12)  // SPI 속도 25MHz

// SD 카드 객체
SdFat SD;
SdFile testFile;

// LCD configuration for Mega2560 (model, cs, cd, wr, rd, reset)
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4);

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing system...");

  // 디스플레이 초기화
  initializeLCD();

  // SD 카드 초기화
  initializeSDCard();

  // SD 카드 테스트
  testSDCard();
}

void loop() {
  // 메인 루프에서 추가 동작 없음
}

void initializeLCD() {
  Serial.println("Initializing LCD...");
  pinMode(LCD_CS, OUTPUT);
  digitalWrite(LCD_CS, LOW);  // LCD 활성화
  mylcd.Init_LCD();           // LCD 초기화
  mylcd.Fill_Screen(BLACK);   // 검은색 화면 출력
  Serial.println("LCD initialized successfully.");
  digitalWrite(LCD_CS, HIGH); // LCD 비활성화
}

void initializeSDCard() {
  Serial.println("Initializing SD card...");
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, LOW);  // SD 카드 활성화

  // SD 카드 초기화 (SPI 속도 설정)
  if (!SD.begin(SD_CS, SPI_SPEED)) {
    Serial.println("SD card initialization failed!");
    Serial.println("Possible causes:");
    Serial.println("1. SD card is not inserted.");
    Serial.println("2. Wiring is incorrect.");
    Serial.println("3. SD card is not formatted as FAT16/FAT32.");
    while (true);  // 실패 시 멈춤
  }
  Serial.println("SD card initialized successfully.");
  digitalWrite(SD_CS, HIGH); // SD 카드 비활성화
}

void testSDCard() {
  Serial.println("Testing SD card...");
  
  // SD 카드 활성화
  digitalWrite(SD_CS, LOW);

  // 파일 생성 및 쓰기
  if (testFile.open("test.txt", O_RDWR | O_CREAT | O_AT_END)) {
    Serial.println("Writing to test.txt...");
    testFile.println("Hello, SdFat!");
    testFile.close();
    Serial.println("Write successful.");
  } else {
    Serial.println("Failed to open test.txt for writing.");
  }

  // 파일 읽기
  if (testFile.open("test.txt", O_READ)) {
    Serial.println("Reading from test.txt:");
    int data;
    while ((data = testFile.read()) >= 0) {
      Serial.write(data);
    }
    testFile.close();
    Serial.println("\nRead successful.");
  } else {
    Serial.println("Failed to open test.txt for reading.");
  }

  // SD 카드 비활성화
  digitalWrite(SD_CS, HIGH);
}
