#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>
#include "DisplayManager.h"
#include "WeatherDataManager.h"
#include "WeatherParser.h"

// LCD configuration
LCDWIKI_KBV lcd(ILI9486, A3, A2, A1, A0, A4);
DisplayManager displayManager(lcd);
WeatherDataManager weatherManager;

void setup() {
    Serial.begin(115200);
    displayManager.initialize();
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        WeatherParser::parseInput(input, weatherManager);
        // Use displayManager to update screen based on `weatherManager` data
    }
}
