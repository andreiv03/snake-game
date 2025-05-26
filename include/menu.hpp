#pragma once

#include "main.hpp"

#define MENU_REFRESH_INTERVAL 1000

enum MenuItem { MENU_START, MENU_SCORES, MENU_SETTINGS, MENU_COUNT };

extern MenuItem selectedMenuItem;

void showMenu();

void handleMenuInput();
