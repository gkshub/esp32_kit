 /**
 * @file       led_indicator.cpp
 * @brief      Manages LED lights
 *
 * @project    ESP32 Weather Station Display
 * @author     Georgekutty Kurian
 * @date       2026-06-22
 *
 * @details
 *
 * @note Dependencies: 
 */

#include <Arduino.h>
#include "led_indicator.h"

LedIndicator::LedIndicator(uint8_t redPin, uint8_t greenPin, uint8_t bluePin) {
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;
  
}

void LedIndicator::hw_init() {
  pinMode(_redPin, OUTPUT);
}
