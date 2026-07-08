#ifndef WEATHER_MANAGER_H
#define WEATHER_MANAGER_H

#include <Arduino.h>
#include "display_manager.h"

// Start the weather fetch task. Pass a pointer to the display so the task
// can update the UI when data arrives.
void startWeatherTask(DisplayManager* displayPtr);

#endif
