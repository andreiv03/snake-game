#include "settings.hpp"

Settings settings;
SettingsItem selectedItem = SETTINGS_COLLISIONS;

void initSettings() { settings.collisions = 0; }

void showSettings() {
  display.firstPage();
  display.setFont(u8g2_font_profont11_tr);

  char setting[16];
  char selectedSetting[16];

  do {
    display.drawStr(0, 10, "Settings");

    for (uint8_t item = 0; item < SETTINGS_COUNT; item++) {
      switch (item) {
      case SETTINGS_COLLISIONS:
        sprintf(setting, "Collisions %s", settings.collisions ? "ON" : "OFF");
        break;

      case SETTINGS_BACK:
        sprintf(setting, "Back");
        break;

      default:
        break;
      }

      sprintf(selectedSetting, "%s%s", (item == selectedItem ? "> " : "  "), setting);
      display.drawStr(0, 24 + item * 10, selectedSetting);
    }

  } while (display.nextPage());
}

void handleSettingsInput() {
  if (appState != STATE_SETTINGS) {
    return;
  }

  static int32_t before = 0;
  const int32_t now = millis();

  if (now - before < DEBOUNCE_DELAY) {
    return;
  }

  if (digitalRead(BUTTON_UP) == LOW) {
    before = now;

    if (selectedItem > 0) {
      selectedItem = static_cast<SettingsItem>(selectedItem - 1);
      showSettings();
    }
  }

  if (digitalRead(BUTTON_DOWN) == LOW) {
    before = now;
    if (selectedItem < SETTINGS_COUNT - 1) {
      selectedItem = static_cast<SettingsItem>(selectedItem + 1);
      showSettings();
    }
  }

  if (digitalRead(BUTTON_SUPPORT) == LOW) {
    before = now;

    switch (static_cast<uint8_t>(selectedItem)) {
    case SETTINGS_COLLISIONS:
      settings.collisions = !settings.collisions;
      showSettings();
      break;

    case SETTINGS_BACK:
      selectedItem = SETTINGS_COLLISIONS;
      selectedMenuItem = MENU_START;
      appState = STATE_MENU;
      showMenu();

      while (digitalRead(BUTTON_SUPPORT) == LOW) {
        delay(10);
      }

      break;

    default:
      break;
    }
  }
}
