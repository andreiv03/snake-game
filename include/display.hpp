#pragma once

#include "main.hpp"
#include <U8g2lib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

extern U8G2_SSD1306_128X64_NONAME_1_HW_I2C display;

void initDisplay();

void showLoadingScreen();

void showEndScreen(uint8_t score, const char *message);
