#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <LCDWIKI_KBV.h>
#include <LCDWIKI_GUI.h>
#include "BitmapManager.h"
#include "WeatherManager.h"

class DisplayManager {
public:
    DisplayManager(LCDWIKI_KBV &lcd);
    void updateDisplay(WeatherManager &weatherManager);

private:
    LCDWIKI_KBV &mylcd;

    void drawHorizontalLine(int y);
    void drawVerticalLine(int x, int yStart, int yEnd);
    void printCenteredText(const char* text, int xStart, int xEnd, int yStart, int yEnd, uint16_t color, uint8_t textSize);
    void printTextInRegion(const char* text, int xStart, int xEnd, int yStart, int lineHeight, uint16_t color, uint8_t textSize, int line);
};

#endif // DISPLAY_MANAGER_H
