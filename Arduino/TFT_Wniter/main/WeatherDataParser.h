#ifndef WEATHER_DATA_PARSER_H
#define WEATHER_DATA_PARSER_H

#include <Arduino.h>

class WeatherDataParser {
private:
    char currentDate[32];
    char weatherStateA[16];
    float temperatureB;
    int humidityC;
    char stateC[16];
    char weatherDataE[3][16];
    bool hasError;

public:
    WeatherDataParser();
    void parseInput(String input);
    const char* getCurrentDate();
    const char* getWeatherStateA();
    float getTemperatureB();
    int getHumidityC();
    const char* getStateC();
    const char* getWeatherDataE(int index);
    bool getErrorState();
};

#endif
