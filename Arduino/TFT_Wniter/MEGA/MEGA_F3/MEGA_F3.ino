#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_KBV.h> // Hardware-specific library
#include "bitmap.h"      // Include bitmap data

#include <DHT.h>  // 온습도 센서 라이브러리
#define DHTPIN 22 // 온습도 센서 핀 번호
#define DHTTYPE DHT11 // 센서 타입 (DHT11 또는 DHT22)
DHT dht(DHTPIN, DHTTYPE);


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
float temperatureB = -1;       // Default for Section B
int humidityC = 65;              // Default for Section C
char stateC[16] = "Proper";      // Default state for Section C
char weatherDataE[3][16] = {"CLR", "SN", "RN"}; // Default for Sections E, F, G
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
    Serial.begin(9600);   // 디버깅용 시리얼
    Serial1.begin(9600);  // ESP8266과 통신용 시리얼
    dht.begin();            // DHT 센서 초기화
    updateDisplay();        // 초기 화면 출력
}


void loop() {
    static String serialBuffer = "";  // 데이터 버퍼
    while (Serial1.available() > 0) {
        char incomingChar = Serial1.read();  // 한 글자씩 읽음
        if (incomingChar == '\n') {         // '\n'으로 데이터 종료
            serialBuffer.trim();            // 공백 제거
            if (serialBuffer.length() > 0) {
                parseSerialInput(serialBuffer);  // 입력 파싱
                updateDisplay();               // 디스플레이 갱신
            }
            serialBuffer = "";  // 버퍼 초기화
        } else {
            serialBuffer += incomingChar;  // 버퍼에 추가
        }
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

    // Section A: Current weather
    mylcd.Set_Text_colour(BLACK);
    mylcd.Set_Text_Size(2);
    mylcd.Print_String(currentDate, 10, 10); // Current date and time

    const unsigned char* bitmapA = mapWeatherToBitmap(weatherStateA);
    drawBitmapScaled((screenWidth - BITMAP_WIDTH * 1.5) / 2,
                     (sectionHeight - BITMAP_HEIGHT * 1.5) / 2,
                     bitmapA, BITMAP_WIDTH, BITMAP_HEIGHT, 1.5);

    // Section B: Temperature
    char tempBuffer[8];
    sprintf(tempBuffer, "%d C", temperatureB); // Use integer format
    printCenteredText(tempBuffer, 0, middleSectionWidth, sectionHeight, 2 * sectionHeight, BLACK, 4);

    // Debugging output for temperature
    Serial.print("Displaying Temperature: ");
    Serial.println(tempBuffer);

    // Section C: Humidity
    printTextInRegion("Humidity", middleSectionWidth, screenWidth, sectionHeight + 20, 16, RED, 2, 0);
    char humidityBuffer[8];
    sprintf(humidityBuffer, "%d%%", humidityC);
    printTextInRegion(humidityBuffer, middleSectionWidth, screenWidth, sectionHeight + 40, 16, BLACK, 2, 1);

    // Section D: State
    printTextInRegion("STATE", middleSectionWidth, screenWidth, sectionHeight + 90, 20, BLUE, 2, 0);
    printTextInRegion(stateC, middleSectionWidth, screenWidth, sectionHeight + 110, 20, BLACK, 2, 1);

    // Sections E, F, G: Future weather
    for (int i = 0; i < 3; i++) {
        const unsigned char* bitmapE = (strcmp(weatherDataE[i], "UNK") == 0) ? weather_error : mapWeatherToBitmap(weatherDataE[i]);
        drawBitmapScaled(i * bottomSectionWidth + (bottomSectionWidth - BITMAP_WIDTH * 0.5) / 2,
                         2 * sectionHeight + (sectionHeight - BITMAP_HEIGHT * 0.5) / 2,
                         bitmapE, BITMAP_WIDTH, BITMAP_HEIGHT, 0.5);
    }

    // Draw dividing lines
    drawHorizontalLine(sectionHeight); // Line between top and middle section
    drawHorizontalLine(2 * sectionHeight); // Line between middle and bottom section

    // Vertical lines in bottom section
    for (int i = 1; i < 3; i++) {
        drawVerticalLine(i * bottomSectionWidth, 2 * sectionHeight, screenHeight);
    }
}

void parseSerialInput(String input) {
    Serial.println("Parsing Serial Input:");
    Serial.println(input);

    hasError = false;  // Reset error flag

    // 1. Parse date and time
    int dateTimeSeparator = input.indexOf('_');
    if (dateTimeSeparator == -1) {
        Serial.println("Error: Invalid input format (missing date and time).");
        hasError = true;
        return;
    }

    String dateStr = input.substring(0, dateTimeSeparator);
    int timeStart = dateTimeSeparator + 1;
    int timeEnd = input.indexOf("_", timeStart); // Check for next "_" to determine time end
    if (timeEnd == -1) {
        timeEnd = input.indexOf("CW|"); // Check for weather data start if "_" is missing
    }
    if (timeEnd == -1 || timeEnd - timeStart > 5) {
        Serial.println("Error: Invalid time format.");
        hasError = true;
        return;
    }

    String timeStr = input.substring(timeStart, timeEnd); // Extract HH:MM
    if (timeStr.length() == 4) {
        timeStr = "0" + timeStr; // Convert '8:08' to '08:08'
    }
    if (timeStr.length() != 5 || timeStr.charAt(2) != ':') {
        Serial.println("Error: Invalid time format (expected HH:MM).\n");
        hasError = true;
        return;
    }

    snprintf(currentDate, sizeof(currentDate), "%s %s", dateStr.c_str(), timeStr.c_str());

    // 반내림하여 현재 시간 계산
    int currentHour = timeStr.substring(0, 2).toInt();
    int currentMinute = timeStr.substring(3, 5).toInt();
    if (currentMinute >= 30) currentHour += 1;  // 30분 이상일 때 반올림

    Serial.print("Rounded Current Hour: ");
    Serial.println(currentHour);

    // 2. Check for DataNotFound
    String weatherData = input.substring(timeEnd + 1); // Extract after second "_"
    if (weatherData.startsWith("DataNotFound")) {
        Serial.println("Warning: DataNotFound received. Setting default error bitmaps.");

        // 미래 날씨 데이터 초기화
        for (int i = 0; i < 3; i++) {
            strncpy(weatherDataE[i], "UNK", sizeof(weatherDataE[i]));
        }
        hasError = true;  // Set error flag
        return;
    }

    // 3. Parse current weather data
    int currentWeatherStart = weatherData.indexOf("CW|W:") + 5;
    if (currentWeatherStart < 5) {
        Serial.println("Error: Missing current weather information.");
        hasError = true;
        return;
    }
    int currentWeatherEnd = weatherData.indexOf('|', currentWeatherStart);
    String currentWeather = weatherData.substring(currentWeatherStart, currentWeatherEnd);
    strncpy(weatherStateA, currentWeather.c_str(), sizeof(weatherStateA));

    // 4. Replace humidity with DHT11 value
    float measuredHumidity = dht.readHumidity();
    if (isnan(measuredHumidity)) {
        Serial.println("Error: Failed to read from DHT sensor.");
        measuredHumidity = 0;  // Default value on error
        hasError = true;
    }
    humidityC = (int)measuredHumidity;  // Replace with sensor value

    strncpy(stateC, humidityC > HUMIDITY_HIGH ? "Ventilation" : 
           (humidityC < HUMIDITY_LOW ? "Humidification" : "Proper"), sizeof(stateC));

    Serial.print("Updated Humidity: ");
    Serial.println(humidityC);

    // 5. Parse future weather data for 'E', 'F', 'G'
    for (int i = 0; i < 3; i++) {
        int futureHour = (currentHour + i + 1) % 24;  // Calculate future hour
        char futureKey[8];
        sprintf(futureKey, "$%02d00|W:", futureHour);  // Generate key (e.g., "$0800|W:")
        int futureStart = weatherData.indexOf(futureKey);
        if (futureStart != -1) {
            futureStart += strlen(futureKey);
            int futureEnd = weatherData.indexOf('|', futureStart);
            String futureWeather = weatherData.substring(futureStart, futureEnd);
            strncpy(weatherDataE[i], futureWeather.c_str(), sizeof(weatherDataE[i]));
        } else {
            strncpy(weatherDataE[i], "UNK", sizeof(weatherDataE[i]));  // Default to unknown
        }
    }

    // Debugging output
    Serial.print("- Current Time: ");
    Serial.println(currentDate);
    Serial.print("- Current Weather: ");
    Serial.println(weatherStateA);
    Serial.print("- Temperature: ");
    Serial.println(temperatureB);
    Serial.print("- Measured Humidity: ");
    Serial.println(humidityC);
    for (int i = 0; i < 3; i++) {
        Serial.print("- Weather +");
        Serial.print(i + 1);
        Serial.print("h: ");
        Serial.println(weatherDataE[i]);
    }
}
