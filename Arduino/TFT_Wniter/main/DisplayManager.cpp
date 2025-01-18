#include "DisplayManager.h"
#include "bitmap.h"

DisplayManager::DisplayManager(LCDWIKI_KBV &lcd) : mylcd(lcd) {}

void DisplayManager::updateDisplay(WeatherManager &weatherManager) {
    // 화면 갱신
    mylcd.Fill_Screen(WHITE);
    int screenHeight = mylcd.Get_Display_Height();
    int screenWidth = mylcd.Get_Display_Width();
    int sectionHeight = screenHeight / 3;
    int middleSectionWidth = screenWidth / 2;
    int bottomSectionWidth = screenWidth / 3;

    // 현재 날짜 출력
    mylcd.Set_Text_colour(BLACK);
    mylcd.Set_Text_Size(2);
    mylcd.Print_String(weatherManager.getCurrentDate(), 10, 10);

    // A 섹션: 현재 날씨 출력
    drawBitmapScaled((screenWidth - BITMAP_WIDTH * 1.5) / 2,
                     (sectionHeight - BITMAP_HEIGHT * 1.5) / 2,
                     weatherManager.getCurrentWeatherBitmap(), BITMAP_WIDTH, BITMAP_HEIGHT, 1.5);

    // B 섹션: 온도 출력
    char tempBuffer[8];
    sprintf(tempBuffer, "%d C", weatherManager.getTemperature());
    printCenteredText(tempBuffer, 0, middleSectionWidth, sectionHeight, 2 * sectionHeight, BLACK, 4);

    // C 섹션: 습도 및 상태 출력
    printTextInRegion("Humidity", middleSectionWidth, screenWidth, sectionHeight + 20, 16, RED, 2, 0);
    char humidityBuffer[8];
    sprintf(humidityBuffer, "%d%%", weatherManager.getHumidity());
    printTextInRegion(humidityBuffer, middleSectionWidth, screenWidth, sectionHeight + 40, 16, BLACK, 2, 1);
    printTextInRegion(weatherManager.getState(), middleSectionWidth, screenWidth, sectionHeight + 110, 20, BLUE, 2, 1);

    // 나머지 코드 생략...
}

// 나머지 유틸리티 함수들 구현...
