#pragma once

#include "main.hpp"
#include <Arduino.h>

#define LED_RED_PIN -1
#define LED_GREEN_PIN 8
#define LED_BLUE_PIN -1

#define FLASH_GREEN_DURATION 100

enum LedEffect { NONE, FLASH_GREEN };

void initLed();

void setLed(uint8_t r, uint8_t g, uint8_t b);

void updateLed();

void flashGreen();
