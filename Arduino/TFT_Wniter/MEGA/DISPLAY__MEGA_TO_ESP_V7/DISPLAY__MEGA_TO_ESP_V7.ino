#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_KBV.h> // Hardware-specific library
#include "bitmap.h"      // Include bitmap data

#include <DHT.h>  // 온습도 센서 라이브러리
#define DHTPIN 22 // 온습도 센서 핀 번호
#define DHTTYPE DHT22 // 센서 타입 (DHT11 또는 DHT22)
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
    sprintf(tempBuffer, "%d C", temperatureB); // Use integer format
    printCenteredText(tempBuffer, 0, middleSectionWidth, sectionHeight, 2 * sectionHeight, BLACK, 4);

    // Debugging output to confirm displayed value
    Serial.print("Displaying Temperature: ");
    Serial.println(tempBuffer);




    // Section C: Humidity
    printTextInRegion("Humidity", middleSectionWidth, screenWidth, sectionHeight + 20, 16, RED, 2, 0);
    char humidityBuffer[8];
    sprintf(humidityBuffer, "%d%%", humidityC);
    // printTextInRegion(humidityBuffer, middleSectionWidth, screenWidth, sectionHeight + 20, 16, BLACK, 2, 1);
    // Adjust Y coordinate to move the humidity value one line lower
    printTextInRegion(humidityBuffer, middleSectionWidth, screenWidth, sectionHeight + 40, 16, BLACK, 2, 1);


    // Section D: State
    printTextInRegion("STATE", middleSectionWidth, screenWidth, sectionHeight + 90, 20, BLUE, 2, 0);
    printTextInRegion(stateC, middleSectionWidth, screenWidth, sectionHeight + 110, 20, BLACK, 2, 1);

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

    hasError = false;  // 오류 플래그 초기화

    // 날짜 및 시간 파싱
    int dateTimeSeparator = input.indexOf('_');
    if (dateTimeSeparator == -1) {
        Serial.println("Error: Invalid input format (missing date and time).");
        hasError = true;
        return; // 디스플레이 갱신하지 않음
    }

    String dateStr = input.substring(0, dateTimeSeparator);
    String timeStr = input.substring(dateTimeSeparator + 1, dateTimeSeparator + 6); // HH:MM 추출
    snprintf(currentDate, sizeof(currentDate), "%s %s", dateStr.c_str(), timeStr.c_str()); // 형식 조정

    int currentHour = timeStr.substring(0, 2).toInt();

    // 현재 날씨 데이터 파싱
    String weatherData = input.substring(dateTimeSeparator + 7); // CW| 이하 추출
    int currentWeatherStart = weatherData.indexOf("CW|W:") + 5;
    if (currentWeatherStart < 5) {
        Serial.println("Error: Missing current weather information.");
        hasError = true;
        return; // 디스플레이 갱신하지 않음
    }
    int currentWeatherEnd = weatherData.indexOf('|', currentWeatherStart);
    String currentWeather = weatherData.substring(currentWeatherStart, currentWeatherEnd);
    strncpy(weatherStateA, currentWeather.c_str(), sizeof(weatherStateA));

    // 온도 데이터 파싱
    int tIndex = weatherData.indexOf("T:");
    if (tIndex > 0) {
        int tEnd = weatherData.indexOf('|', tIndex);
        if (tEnd == -1) tEnd = weatherData.length();
        temperatureB = round(weatherData.substring(tIndex + 2, tEnd).toFloat());
        Serial.print("Updated Temperature: ");
        Serial.println(temperatureB);
    } else {
        Serial.println("Warning: Missing temperature data. Using default value.");
        temperatureB = 0;
    }

    // 습도 데이터 파싱 및 센서 값으로 치환
    float measuredHumidity = dht.readHumidity();
    if (isnan(measuredHumidity)) {
        Serial.println("Error: Failed to read from DHT sensor.");
        measuredHumidity = 0; // 오류 시 기본값
        hasError = true;
    }
    humidityC = (int)measuredHumidity; // 습도 값을 센서 데이터로 치환
    strncpy(stateC, humidityC > HUMIDITY_HIGH ? "Ventilation" : 
           (humidityC < HUMIDITY_LOW ? "Humidification" : "Proper"), sizeof(stateC));
    Serial.print("Measured Humidity (Replaced): ");
    Serial.println(humidityC);

    // 미래 날씨 데이터 파싱
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

    // 디버깅 출력
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
