#pragma once

#include "main.hpp"
#include <Arduino.h>

enum SettingsItem { SETTINGS_COLLISIONS, SETTINGS_BACK, SETTINGS_COUNT };

struct Settings {
  uint8_t collisions;
};

extern Settings settings;

void initSettings();

void showSettings();

void handleSettingsInput();
