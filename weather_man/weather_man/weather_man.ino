#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>


#include "config.h"
#include "display_manager.h"
#include "led_indicator.h"

// secrets.h contains Keys and sensitive information
// This should not be checked-in
#include "secrets.h"

#include "weather_manager.h"

DisplayManager display(Config::Display::SCREEN_WIDTH, Config::Display::SCREEN_HEIGHT, &Wire, -1);
LedIndicator led_indicator(Config::Pins::redledPin, Config::Pins::redledPin, Config::Pins::redledPin);
// Task Handlers (Optional, but good practice for tracking tasks)
TaskHandle_t TaskOLEDHandle = NULL;
TaskHandle_t TaskLEDHandle = NULL;

#if ENABLE_CPU_MONITOR
TaskHandle_t TaskCPUMonitorHandle = NULL;
#endif

// Define the Task Functions before setup
void TaskOLED(void *pvParameters);
void TaskLED(void *pvParameters);

#if ENABLE_CPU_MONITOR
void TaskCPUMonitor(void *pvParameters);
#endif

void setup() {
  Serial.begin(Config::System::SERIAL_BAUD);
  led_indicator.hw_init();

  display.begin(Config::Display::i2cAddr); 

  // --- FreeRTOS Task Creation ---
  
  // Create OLED Task
  xTaskCreatePinnedToCore(
    TaskOLED,          // Function that implements the task
    "OLED_Scroll",     // Text name for the task (for debugging)
    2048,              // Stack size in words (increase if complex gfx are added)
    NULL,              // Parameter passed into the task
    1,                 // Task priority (1 = low, higher numbers = higher priority)
    &TaskOLEDHandle,   // Task handle
    1                  // Core ID (0 or 1 for ESP32; omit if using standard FreeRTOS)
  );

  // Create LED Blinking Task
  xTaskCreatePinnedToCore(
    TaskLED,
    "LED_Blink",
    1024,              // Smaller stack size needed for simple GPIO toggling
    NULL,
    1,                 // Same priority means they will share CPU time evenly
    &TaskLEDHandle,
    1
  );

#if ENABLE_CPU_MONITOR
  xTaskCreatePinnedToCore(
    TaskCPUMonitor,    // Function name
    "CPU_Monitor",     // Task name
    2048,              // Stack size
    NULL,              // Parameter
    1,                 // Low priority so it doesn't interrupt critical tasks
    NULL,              // Task handle
    1                  // Core ID
  );
#endif

  // Start weather fetch task (connects to WiFi and updates display)
  startWeatherTask(&display);
}

void loop() {
  // FreeRTOS takes over execution control. 
  // Leave loop() completely empty, or use vTaskDelete(NULL) to delete it.
  vTaskDelay(pdMS_TO_TICKS(1000)); 
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

// Task 1: Handles the OLED scrolling animation
void TaskOLED(void *pvParameters) {
  (void) pvParameters; // Unused parameter

  for (;;) { // Tasks must run in an infinite loop
    display.startscrollright(0x00, 0x0F);
    // Non-blocking delay: Allows other tasks to run while this task "sleeps"
    vTaskDelay(pdMS_TO_TICKS(7000)); 
    
    display.stopscroll();
    vTaskDelay(pdMS_TO_TICKS(1000));
    
    display.startscrollleft(0x00, 0x0F);
    vTaskDelay(pdMS_TO_TICKS(7000));
    
    display.stopscroll();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// Task 2: Handles the LED flashing logic
void TaskLED(void *pvParameters) {
  (void) pvParameters;
  
  bool ledState = false;
  constexpr int ledPin = Config::Pins::redledPin;

  for (;;) {
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    Serial.println(ledState);
    
    ledState = !ledState; // Toggle state
    
    // Toggle every 1000ms without interrupting the OLED scroll
    vTaskDelay(pdMS_TO_TICKS(1000)); 
  }
}

#if ENABLE_CPU_MONITOR
void TaskCPUMonitor(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    // Allocate a buffer large enough to hold the text table
    // (Roughly 40 characters per task is a safe estimate)
    char statsBuffer[1024];
    
    Serial.println(F("\n--- FREE RTOS CPU UTILIZATION STATS ---"));
    
    // Pass the buffer to the FreeRTOS stats collector
    vTaskGetRunTimeStats(statsBuffer);
    
    // Print the formatted table directly to the console
    Serial.print(statsBuffer);
    
    // Wait 5 seconds before checking again
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}
#endif
