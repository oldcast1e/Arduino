#ifndef WEATHERDATAMANAGER_H
#define WEATHERDATAMANAGER_H

class WeatherDataManager {
private:
    char currentDate[32] = "";
    char weatherStateA[16] = "CLR";
    float temperatureB = 25;
    int humidityC = 65;
    char stateC[16] = "Proper";
    char weatherDataE[3][16] = {"CLR", "SN", "RN"};
    bool hasError = false;

public:
    void setCurrentDate(const char* date) {
        strncpy(currentDate, date, sizeof(currentDate));
    }

    void setWeatherStateA(const char* state) {
        strncpy(weatherStateA, state, sizeof(weatherStateA));
    }

    void setTemperatureB(float temp) {
        temperatureB = round(temp);
    }

    void setHumidityC(int humidity) {
        humidityC = humidity;
        strncpy(stateC, humidity > 70 ? "Ventilation" : (humidity < 30 ? "Humidification" : "Proper"), sizeof(stateC));
    }

    void setFutureWeather(int index, const char* state) {
        if (index >= 0 && index < 3) {
            strncpy(weatherDataE[index], state, sizeof(weatherDataE[index]));
        }
    }

    const char* getCurrentDate() const { return currentDate; }
    const char* getWeatherStateA() const { return weatherStateA; }
    float getTemperatureB() const { return temperatureB; }
    int getHumidityC() const { return humidityC; }
    const char* getStateC() const { return stateC; }
    const char* getFutureWeather(int index) const { return weatherDataE[index]; }
    bool hasErrorState() const { return hasError; }
    void setErrorState(bool state) { hasError = state; }
};

#endif
