#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_KBV.h> // Hardware-specific library
#include "bitmap.h" // Include bitmap data
#include <Wire.h>

// LCD configuration
LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4);

// Color definitions
#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED   0xF800
#define BLUE  0x001F

// Humidity thresholds
#define HUMIDITY_LOW 30
#define HUMIDITY_HIGH 70

// Update interval (30 seconds)
#define UPDATE_INTERVAL 30000

// Weather data storage
char weatherStateA[16] = "CLR"; 
int temperatureB = 25; 
int humidityC = 65; 
char stateC[16] = "Proper"; 
char weatherDataE[3][16] = {"CLR", "CLD", "OVC"}; 

// Date-time storage
char currentDateTime[32] = "2025.1.1.00:00";

// Timing variables
unsigned long lastUpdate = 0;

// Function prototypes
void drawHorizontalLine(int y);
void drawVerticalLine(int x, int yStart, int yEnd);
void clearRegion(int xStart, int xEnd, int yStart, int yEnd);
void printCenteredText(const char* text, int xStart, int xEnd, int yStart, int yEnd, uint16_t color, uint8_t textSize);
const unsigned char* mapWeatherToBitmap(const char* weatherCode);
void drawBitmapScaled(int16_t x, int16_t y, const unsigned char *bitmap, int16_t w, int16_t h, float scale);
void updateDisplay();
void parseSerialInput(String input);

// Utility functions
const char* determineState(int humidity) {
    if (humidity < HUMIDITY_LOW) return "Humidification";
    if (humidity > HUMIDITY_HIGH) return "Ventilation";
    return "Proper";
}

void setup() {
    mylcd.Init_LCD();
    mylcd.Fill_Screen(WHITE);
    Serial.begin(9600);
    Wire.begin();
    updateDisplay();
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        if (millis() - lastUpdate >= UPDATE_INTERVAL) {
            parseSerialInput(input);
            updateDisplay();
            lastUpdate = millis();
        }
    }
}

// Parsing serial input
void parseSerialInput(String input) {
    int dateIndex = input.indexOf('_');
    if (dateIndex > 0) {
        strncpy(currentDateTime, input.substring(0, dateIndex).c_str(), sizeof(currentDateTime));
        input = input.substring(dateIndex + 1);
    }
    Serial.print("Current DateTime: ");
    Serial.println(currentDateTime);

    // Parsing the weather information
    if (input.startsWith("CW|")) {
        int weatherIndex = input.indexOf("W:") + 2;
        strncpy(weatherStateA, input.substring(weatherIndex, weatherIndex + 3).c_str(), sizeof(weatherStateA));
    }
    Serial.print("Current Weather: ");
    Serial.println(weatherStateA);

    // Parsing hourly forecasts
    for (int i = 0; i < 3; i++) {
        int timeIndex = input.indexOf(String(i * 100 + 100).c_str());
        if (timeIndex > 0) {
            int wIndex = input.indexOf("W:", timeIndex) + 2;
            strncpy(weatherDataE[i], input.substring(wIndex, wIndex + 3).c_str(), sizeof(weatherDataE[i]));
        } else {
            strncpy(weatherDataE[i], "UNK", sizeof(weatherDataE[i]));
        }
    }
}

// Updating the display
void updateDisplay() {
    int screenHeight = mylcd.Get_Display_Height();
    int screenWidth = mylcd.Get_Display_Width();
    int sectionHeight = screenHeight / 3;

    // Clear and redraw lines
    drawHorizontalLine(sectionHeight);
    drawHorizontalLine(2 * sectionHeight);
    drawVerticalLine((3 * screenWidth) / 5, sectionHeight, 2 * sectionHeight);
    for (int i = 1; i < 3; i++) {
        drawVerticalLine(i * (screenWidth / 3), 2 * sectionHeight, screenHeight);
    }

    // Update each section
    clearRegion(0, screenWidth, 0, sectionHeight);
    drawBitmapScaled((screenWidth - BITMAP_WIDTH * 1.5) / 2, (sectionHeight - BITMAP_HEIGHT * 1.5) / 2, mapWeatherToBitmap(weatherStateA), BITMAP_WIDTH, BITMAP_HEIGHT, 1.5);
    
    clearRegion(0, (3 * screenWidth) / 5, sectionHeight, 2 * sectionHeight);
    char temp[16];
    sprintf(temp, "%d C", temperatureB);
    printCenteredText(temp, 0, (3 * screenWidth) / 5, sectionHeight, 2 * sectionHeight, BLACK, 4);

    clearRegion((3 * screenWidth) / 5, screenWidth, sectionHeight, 2 * sectionHeight);
    char humidity[16];
    sprintf(humidity, "H:%d%%", humidityC);
    printCenteredText(humidity, (3 * screenWidth) / 5, screenWidth, sectionHeight, 2 * sectionHeight, RED, 2);

    for (int i = 0; i < 3; i++) {
        clearRegion(i * (screenWidth / 3), (i + 1) * (screenWidth / 3), 2 * sectionHeight, screenHeight);
        drawBitmapScaled((i * screenWidth / 3 + (screenWidth / 6)) - (BITMAP_WIDTH / 2), (2 * sectionHeight + (sectionHeight / 2)) - (BITMAP_HEIGHT / 2), mapWeatherToBitmap(weatherDataE[i]), BITMAP_WIDTH, BITMAP_HEIGHT, 0.5);
    }

    // Redraw section dividing lines to ensure they remain visible
    drawHorizontalLine(sectionHeight);
    drawHorizontalLine(2 * sectionHeight);
    drawVerticalLine((3 * screenWidth) / 5, sectionHeight, 2 * sectionHeight);
    for (int i = 1; i < 3; i++) {
        drawVerticalLine(i * (screenWidth / 3), 2 * sectionHeight, screenHeight);
    }
}

// Function implementations
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
    int charWidth = 6 * textSize; 
    int charHeight = 8 * textSize; 
    int textWidth = charWidth * strlen(text); 
    int textHeight = charHeight; 

    int x = xStart + (xEnd - xStart - textWidth) / 2; 
    int y = yStart + (yEnd - yStart - textHeight) / 2; 

    mylcd.Set_Text_colour(color);
    mylcd.Set_Text_Back_colour(WHITE);
    mylcd.Set_Text_Size(textSize);
    mylcd.Print_String(text, x, y);
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
        return weather_cloudy;
    } else if (strcmp(weatherCode, "OVC") == 0) {
        return weather_cloud;
    } else {
        return weather_sun; 
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

