#ifndef LED_INDICATOR_H
#define LED_INDICATOR_H

#include <stdint.h> // data types to be recognised...


#include "config.h"

class LedIndicator {
  
  private:
    uint8_t _redPin;
    uint8_t _greenPin;
    uint8_t _bluePin;
  
  public:
    // Constructor: Only assigns pins
    LedIndicator(uint8_t redPin, uint8_t greenPin, uint8_t bluePin);

    void hw_init();

  
};

#endif