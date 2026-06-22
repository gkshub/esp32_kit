#ifndef CONFIG_H
#define CONFIG_H

// adhering to modern c++ by using constexpr

namespace Config {

  namespace System {
        constexpr unsigned long SERIAL_BAUD = 115200;
    }
  namespace Display {
    // OLED Display definitions
    constexpr int SCREEN_HEIGHT = 64; 
    constexpr int SCREEN_WIDTH = 128; 

    constexpr uint8_t i2cAddr = 0x3c;

  }
  namespace Pins {
    // Pin definitions
    constexpr int redledPin = 5;   

  }
  namespace WiFi {

  }
  namespace Timing {
    constexpr unsigned long WEATHER_FETCH_INTERVAL = 60 * 1000 *10; // 10mins
  }
}




#endif