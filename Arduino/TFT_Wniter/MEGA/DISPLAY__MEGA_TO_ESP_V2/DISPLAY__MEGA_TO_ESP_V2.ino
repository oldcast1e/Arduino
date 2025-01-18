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
float temperatureB = 25.0;       // Default for Section B
int humidityC = 65;              // Default for Section C
char stateC[16] = "Proper";      // Default state for Section C
char weatherDataE[3][16] = {"CLR", "CLD", "OVC"}; // Default for Sections E, F, G
bool hasError = false;           // Flag to indicate error state

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
    Serial.begin(115200);
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

// Drawing and printing functions (unchanged)
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

void printTextInRegion(const char* text, int xStart, int xEnd, int yStart, int lineHeight, uint16_t color, uint8_t textSize, int line) {
    int y = yStart + line * lineHeight;
    mylcd.Set_Text_colour(color);
    mylcd.Set_Text_Back_colour(WHITE);
    mylcd.Set_Text_Size(textSize);
    mylcd.Print_String(text, xStart + (xEnd - xStart - strlen(text) * 6 * textSize) / 2, y);
}

const unsigned char* mapWeatherToBitmap(const char* weatherCode) {
    if (hasError) {
        return weather_error; // Use error bitmap if in error state
    }
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

void updateDisplay() {
    int screenHeight = mylcd.Get_Display_Height();
    int screenWidth = mylcd.Get_Display_Width();
    int sectionHeight = screenHeight / 3;
    int middleSectionWidth = screenWidth / 2;
    int bottomSectionWidth = screenWidth / 3;

    // Clear entire screen
    mylcd.Fill_Screen(WHITE);

    // Display current date and time in top-left corner
    mylcd.Set_Text_colour(BLACK);
    mylcd.Set_Text_Size(2);
    mylcd.Print_String(currentDate, 10, 10);

    // Section A: Current weather
    const unsigned char* bitmapA = mapWeatherToBitmap(weatherStateA);
    drawBitmapScaled((screenWidth - BITMAP_WIDTH * 1.5) / 2,
                     (sectionHeight - BITMAP_HEIGHT * 1.5) / 2,
                     bitmapA, BITMAP_WIDTH, BITMAP_HEIGHT, 1.5);

    // Section B: Temperature
    char tempBuffer[8];
    sprintf(tempBuffer, "%.1f C", temperatureB);
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
    drawHorizontalLine(sectionHeight);
    drawHorizontalLine(2 * sectionHeight);
    drawVerticalLine(middleSectionWidth, sectionHeight, 2 * sectionHeight);
    for (int i = 1; i < 3; i++) {
        drawVerticalLine(i * bottomSectionWidth, 2 * sectionHeight, screenHeight);
    }
}

void parseSerialInput(String input) {
    Serial.println("Parsing Serial Input:");
    Serial.println(input);

    hasError = false; // Reset error flag

    // Parse the date and time
    int dateEnd = input.indexOf('_');
    if (dateEnd == -1) {
        Serial.println("Error: Invalid input format (date and time missing).");
        hasError = true;
        return;
    }
    String dateStr = input.substring(0, dateEnd);
    strncpy(currentDate, dateStr.c_str(), sizeof(currentDate));

    // Extract current hour
    int currentHourStart = dateStr.lastIndexOf(' ') + 1;
    int currentHour = dateStr.substring(currentHourStart, currentHourStart + 2).toInt();

    // Check for "$NoData"
    if (input.indexOf("$NoData") != -1) {
        Serial.println("Warning: No weather data available. Displaying error bitmaps.");
        hasError = true;
        return;
    }

    // Parse weather data
    String weatherData = input.substring(dateEnd + 1);

    // Update current weather for Section A
    int currentWeatherStart = weatherData.indexOf("CW|W:") + 5;
    if (currentWeatherStart < 5) {
        Serial.println("Error: Missing current weather information.");
        hasError = true;
        return;
    }
    int currentWeatherEnd = weatherData.indexOf('|', currentWeatherStart);
    String currentWeather = weatherData.substring(currentWeatherStart, currentWeatherEnd);
    strncpy(weatherStateA, currentWeather.c_str(), sizeof(weatherStateA));

    // Update B section temperature
    int tIndex = weatherData.indexOf("T:");
    if (tIndex > 0) {
        int tEnd = weatherData.indexOf('|', tIndex);
        temperatureB = weatherData.substring(tIndex + 2, tEnd).toFloat(); // Handle decimal temperatures
    } else {
        Serial.println("Warning: Missing temperature data. Using default value.");
    }

    // Update C section humidity
    int hIndex = weatherData.indexOf("H:");
    if (hIndex > 0) {
        int hEnd = weatherData.indexOf('|', hIndex);
        humidityC = weatherData.substring(hIndex + 2, hEnd).toInt();
        strncpy(stateC, humidityC > HUMIDITY_HIGH ? "Ventilation" : (humidityC < HUMIDITY_LOW ? "Humidification" : "Proper"), sizeof(stateC));
    } else {
        Serial.println("Warning: Missing humidity data. Using default value.");
    }

    // Extract future weather for Sections E, F, G
    for (int i = 0; i < 3; i++) {
        int futureHour = (currentHour + i + 1) % 24;
        char futureKey[8];
        sprintf(futureKey, "$%02d00|W:", futureHour);
        int futureStart = weatherData.indexOf(futureKey);
        if (futureStart != -1) {
            futureStart += strlen(futureKey);
            int futureEnd = weatherData.indexOf('|', futureStart);
            String futureWeather = weatherData.substring(futureStart, futureEnd);
            strncpy(weatherDataE[i], futureWeather.c_str(), sizeof(weatherDataE[i]));
        } else {
            strncpy(weatherDataE[i], "UNK", sizeof(weatherDataE[i]));
        }
    }

    // Debugging output
    Serial.print("- 현재 시간 : ");
    Serial.println(dateStr);
    Serial.print("- 현재 날씨 : ");
    Serial.println(weatherStateA);
    Serial.print("- 1시간 뒤의 날씨 : ");
    Serial.println(weatherDataE[0]);
    Serial.print("- 2시간 뒤의 날씨 : ");
    Serial.println(weatherDataE[1]);
    Serial.print("- 3시간 뒤의 날씨 : ");
    Serial.println(weatherDataE[2]);
}
