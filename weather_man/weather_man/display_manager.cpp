 /**
 * @file       display_manager.cpp
 * @brief      Manages OLED initialization, UI rendering, and screen updates.
 *
 * @project    ESP32 Weather Station Display
 * @author     Georgekutty Kurian
 * @date       2026-06-22
 *
 * @details
 * This module provides an abstraction over the OLED display driver
 * (Adafruit_SSD1306). It handles:
 *
 * - Display initialization
 * - UI layout management
 * - Periodic screen updates
 * - Rendering sensor data (temperature, humidity, system status)
 *
 * @note Dependencies: Adafruit_SSD1306, Adafruit_GFX
 */


// The Adafruit_GFX library for Arduino provides a common syntax and set of graphics functions 
// for all of our LCD and OLED displays and LED matrices.
#include <Adafruit_GFX.h>

// This is a library for our Monochrome OLEDs based on SSD1306 drive
#include <Adafruit_SSD1306.h>

#include "config.h"
#include "display_manager.h"


DisplayManager::DisplayManager(uint8_t width, uint8_t height, TwoWire *twi, int8_t rst_pin) 
    : Adafruit_SSD1306(width, height, twi, rst_pin) // <-- This calls the Adafruit constructor
{
    // Bring up OLED display modules
}

void DisplayManager::begin(uint8_t i2cAddr) {
    // Call the base class begin method to kick off I2C and allocation
    if(!Adafruit_SSD1306::begin(SSD1306_SWITCHCAPVCC, i2cAddr)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
  

    clearDisplay();
    //setTextSize(2);
    //setTextColor(WHITE);
    //setCursor(0, 30);
    //println("678");
    display();

    clearDisplay();

    // A 16x16 pixel custom welcome icon/emoji
  const unsigned char welcome_emoji[] PROGMEM = {
      0x03, 0xc0, 0x0f, 0xf0, 0x1e, 0x78, 0x3c, 0x3c, 
      0x78, 0x1e, 0x71, 0x8e, 0x63, 0xc6, 0x67, 0xe6, 
      0x67, 0xe6, 0x63, 0xc6, 0x71, 0x8e, 0x78, 0x1e, 
      0x3c, 0x3c, 0x1e, 0x78, 0x0f, 0xf0, 0x03, 0xc0
  };
    // Parameters: (x_pos, y_pos, bitmap_array, width, height, color)
  drawBitmap(32, 16, welcome_emoji, 16, 16, SSD1306_WHITE);

  display();
}

