//테스트 완료

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED 디스플레이 설정
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// SPI 핀 설정
#define OLED_MOSI 11
#define OLED_CLK 13
#define OLED_DC 8
#define OLED_CS 10
#define OLED_RESET 9

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  Serial.begin(9600);

  // 디스플레이 초기화
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();

  // 텍스트 출력 테스트
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Hello, OLED!"));
  display.display();
}

void loop() {
  // 반복 동작 추가 가능
}
