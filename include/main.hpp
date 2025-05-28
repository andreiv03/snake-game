#pragma once

#include "display.hpp"
#include "game.hpp"
#include "led.hpp"
#include "menu.hpp"
#include "rtc.hpp"
#include "scores.hpp"
#include "settings.hpp"

#include <Arduino.h>

#define BUTTON_UP 2
#define BUTTON_LEFT 3
#define BUTTON_DOWN 4
#define BUTTON_RIGHT 8
#define BUTTON_SUPPORT 6

#define DEBOUNCE_DELAY 200

enum AppState { STATE_MENU, STATE_PLAYING, STATE_SCORES, STATE_SETTINGS, STATES_COUNT };

extern AppState appState;
