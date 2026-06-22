#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

/**
 * @class DisplayManager
 * @brief Handles OLED UI rendering for the ESP32 weather station.
 */

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"



class DisplayManager : public Adafruit_SSD1306 {

  public: 
    DisplayManager(uint8_t w, uint8_t h, TwoWire *twi = &Wire,
                   int8_t rst_pin = -1);
    void begin(uint8_t i2cAddr);
    //void showWeather(float temp, bool is_rainy);

};

#endif
