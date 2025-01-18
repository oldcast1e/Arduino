#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_KBV.h> // Hardware-specific library
#include "bitmap.h"      // Include bitmap data

// LCD configuration for Mega2560 (model, cs, cd, wr, rd, reset)
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4);

// Define color values
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define BLUE    0x001F

// Define thresholds for humidity levels
#define HUMIDITY_LOW 30
#define HUMIDITY_HIGH 70

// Time interval for updates
#define UPDATE_INTERVAL 5000 // 5 seconds

// Variables to store the current weather information
char currentDate[32] = "";       // Current date and time
char weatherStateA[16] = "CLR";  // Default for Section A
int temperatureB = 25;           // Default for Section B
int humidityC = 65;              // Default for Section C
char stateC[16] = "Proper";      // Default state for Section C
char weatherDataE[3][16] = {"CLR", "CLD", "OVC"}; // Default for Sections E, F, G

// Function declarations
void drawHorizontalLine(int y);
void drawVerticalLine(int x, int yStart, int yEnd);
void clearRegion(int xStart, int xEnd, int yStart, int yEnd);
void printCenteredText(const char* text, int xStart, int xEnd, int yStart, int yEnd, uint16_t color, uint8_t textSize);
void printTextInRegion(const char* text, int xStart, int xEnd, int yStart, int lineHeight, uint16_t color, uint8_t textSize, int line);
const unsigned char* mapWeatherToBitmap(const char* weatherCode);
void drawBitmapScaled(int16_t x, int16_t y, const unsigned char *bitmap, int16_t w, int16_t h, float scale);
void updateDisplay();
void parseSerialInput(String input);

void setup() {
    mylcd.Init_LCD();
    mylcd.Fill_Screen(WHITE);
    Serial.begin(9600);
    updateDisplay();
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        parseSerialInput(input);
        updateDisplay();
        delay(UPDATE_INTERVAL);
    }
}

// Function definitions

void drawHorizontalLine(int y) {
    mylcd.Set_Draw_color(BLACK);
    mylcd.Draw_Line(0, y, mylcd.Get_Display_Width() - 1, y);
}

void drawVerticalLine(int x, int yStart, int yEnd) {
    mylcd.Set_Draw_color(BLACK);
    mylcd.Draw_Line(x, yStart, x, yEnd);
}

void clearRegion(int xStart, int xEnd, int yStart, int yEnd) {
    mylcd.Set_Draw_color(WHITE);
    for (int y = yStart; y <= yEnd; y++) {
        mylcd.Draw_Line(xStart, y, xEnd, y);
    }
}

void printCenteredText(const char* text, int xStart, int xEnd, int yStart, int yEnd, uint16_t color, uint8_t textSize) {
    int charWidth = 6 * textSize;  // Approximate character width in pixels
    int charHeight = 8 * textSize; // Approximate character height in pixels
    int textWidth = charWidth * strlen(text);  // Total text width based on number of characters
    int textHeight = charHeight;  // Single-line height

    int x = xStart + (xEnd - xStart - textWidth) / 2; // Center text horizontally
    int y = yStart + (yEnd - yStart - textHeight) / 2; // Center text vertically

    mylcd.Set_Text_colour(color);
    mylcd.Set_Text_Back_colour(WHITE);
    mylcd.Set_Text_Size(textSize);
    mylcd.Print_String(text, x, y);
}

void printTextInRegion(const char* text, int xStart, int xEnd, int yStart, int lineHeight, uint16_t color, uint8_t textSize, int line) {
    int y = yStart + line * lineHeight; // Calculate the Y position for the line
    mylcd.Set_Text_colour(color);
    mylcd.Set_Text_Back_colour(WHITE);
    mylcd.Set_Text_Size(textSize);
    mylcd.Print_String(text, xStart + (xEnd - xStart - strlen(text) * 6 * textSize) / 2, y);
}

const unsigned char* mapWeatherToBitmap(const char* weatherCode) {
    if (strcmp(weatherCode, "CLR") == 0) {
        return weather_sun;
    } else if (strcmp(weatherCode, "RN") == 0 || strcmp(weatherCode, "RS") == 0 ||
               strcmp(weatherCode, "SH") == 0 || strcmp(weatherCode, "DZ") == 0 || strcmp(weatherCode, "DS") == 0) {
        return weather_rain;
    } else if (strcmp(weatherCode, "SN") == 0 || strcmp(weatherCode, "FL") == 0) {
        return weather_snow;
    } else if (strcmp(weatherCode, "CLD") == 0) {
        return weather_cloud;
    } else if (strcmp(weatherCode, "OVC") == 0) {
        return weather_cloudy;
    } else {
        return weather_sun; // Default to sunny
    }
}

void drawBitmapScaled(int16_t x, int16_t y, const unsigned char *bitmap, int16_t w, int16_t h, float scale) {
    int scaledWidth = w * scale;
    int scaledHeight = h * scale;

    for (int16_t j = 0; j < scaledHeight; j++) {
        for (int16_t i = 0; i < scaledWidth; i++) {
            int16_t originalX = i / scale;
            int16_t originalY = j / scale;
            uint16_t byteIndex = (originalY * w + originalX) / 8;
            uint8_t bitIndex = originalX % 8;
            uint8_t byte = pgm_read_byte(&bitmap[byteIndex]);
            if (byte & (0x80 >> bitIndex)) {
                mylcd.Set_Draw_color(BLACK);
                mylcd.Draw_Pixel(x + i, y + j);
            } else {
                mylcd.Set_Draw_color(WHITE);
                mylcd.Draw_Pixel(x + i, y + j);
            }
        }
    }
}

void updateDisplay() {
    int screenHeight = mylcd.Get_Display_Height();
    int screenWidth = mylcd.Get_Display_Width();
    int sectionHeight = screenHeight / 3;
    int middleSectionWidth = screenWidth / 2;
    int bottomSectionWidth = screenWidth / 3;

    // Clear entire screen
    mylcd.Fill_Screen(WHITE);

    // Section A: Current weather
    const unsigned char* bitmapA = mapWeatherToBitmap(weatherStateA);
    drawBitmapScaled((screenWidth - BITMAP_WIDTH * 1.5) / 2,
                     (sectionHeight - BITMAP_HEIGHT * 1.5) / 2,
                     bitmapA, BITMAP_WIDTH, BITMAP_HEIGHT, 1.5);

    // Section B: Temperature
    char tempBuffer[8];
    sprintf(tempBuffer, "%d C", temperatureB);
    printCenteredText(tempBuffer, 0, middleSectionWidth, sectionHeight, 2 * sectionHeight, BLACK, 4);

    // Section C: Humidity
    printTextInRegion("Humidity", middleSectionWidth, screenWidth, sectionHeight + 20, 16, RED, 2, 0);
    char humidityBuffer[8];
    sprintf(humidityBuffer, "%d%%", humidityC);
    printTextInRegion(humidityBuffer, middleSectionWidth, screenWidth, sectionHeight + 20, 16, BLACK, 2, 1);

    // Section D: State
    printTextInRegion("STATE", middleSectionWidth, screenWidth, sectionHeight + 90, 20, BLUE, 2, 0);
    printTextInRegion(stateC, middleSectionWidth, screenWidth, sectionHeight + 90, 20, BLACK, 2, 1);


    // Sections E, F, G: Future weather
    for (int i = 0; i < 3; i++) {
        const unsigned char* bitmapE = mapWeatherToBitmap(weatherDataE[i]);
        drawBitmapScaled(i * bottomSectionWidth + (bottomSectionWidth - BITMAP_WIDTH * 0.5) / 2,
                         2 * sectionHeight + (sectionHeight - BITMAP_HEIGHT * 0.5) / 2,
                         bitmapE, BITMAP_WIDTH, BITMAP_HEIGHT, 0.5);
    }

    // Draw dividing lines
    drawHorizontalLine(sectionHeight);    // Between A and B sections
    drawHorizontalLine(2 * sectionHeight); // Between D and E sections
    drawVerticalLine(middleSectionWidth, sectionHeight, 2 * sectionHeight); // Separate C and D sections
    for (int i = 1; i < 3; i++) {
        drawVerticalLine(i * bottomSectionWidth, 2 * sectionHeight, screenHeight);
    }
}

void parseSerialInput(String input) {
    Serial.println("Parsing Serial Input:");
    Serial.println(input);

    // Parse the date and time
    int dateEnd = input.indexOf('_');
    String dateStr = input.substring(0, dateEnd);
    strncpy(currentDate, dateStr.c_str(), sizeof(currentDate));

    // Extract current hour
    int currentHour = dateStr.substring(dateStr.lastIndexOf('.') + 1, dateStr.lastIndexOf(':')).toInt();

    // Parse weather data
    String weatherData = input.substring(dateEnd + 1);

    // Update current weather for Section A
    int currentWeatherStart = weatherData.indexOf("CW|W:") + 5;
    int currentWeatherEnd = weatherData.indexOf('|', currentWeatherStart);
    String currentWeather = weatherData.substring(currentWeatherStart, currentWeatherEnd);
    strncpy(weatherStateA, currentWeather.c_str(), sizeof(weatherStateA));

    // Update B section temperature
    int tIndex = weatherData.indexOf("T:");
    if (tIndex > 0) {
        int tEnd = weatherData.indexOf('|', tIndex);
        temperatureB = weatherData.substring(tIndex + 2, tEnd).toInt();
    }

    // Update C section humidity
    int hIndex = weatherData.indexOf("H:");
    if (hIndex > 0) {
        int hEnd = weatherData.indexOf('|', hIndex);
        humidityC = weatherData.substring(hIndex + 2, hEnd).toInt();
        strncpy(stateC, humidityC > HUMIDITY_HIGH ? "Ventilation" : (humidityC < HUMIDITY_LOW ? "Humidification" : "Proper"), sizeof(stateC));
    }

    // Update future weather for Sections E, F, G
    for (int i = 0; i < 3; i++) {
        int futureHour = (currentHour + i + 1) % 24;
        char futureKey[8];
        sprintf(futureKey, "$%02d00|W:", futureHour);
        int futureStart = weatherData.indexOf(futureKey);
        if (futureStart != -1) {
            futureStart += strlen(futureKey);
            int futureEnd = weatherData.indexOf('|', futureStart);
            strncpy(weatherDataE[i], weatherData.substring(futureStart, futureEnd).c_str(), sizeof(weatherDataE[i]));
        } else {
            strncpy(weatherDataE[i], "UNK", sizeof(weatherDataE[i]));
        }
    }
}
