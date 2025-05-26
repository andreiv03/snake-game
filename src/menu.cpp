#include "menu.hpp"

MenuItem selectedMenuItem = MENU_START;
uint32_t lastMenuRefresh = 0;

void showMenu() {
  display.firstPage();
  display.setFont(u8g2_font_profont11_tr);

  char itemName[16];
  char selectedItemName[16];
  char timeString[16];

  do {
    for (uint8_t item = 0; item < MENU_COUNT; item++) {
      switch (item) {
      case MENU_START:
        strcpy(itemName, "Start Game");
        break;

      case MENU_SCORES:
        strcpy(itemName, "Scores");
        break;

      case MENU_SETTINGS:
        strcpy(itemName, "Settings");
        break;

      default:
        break;
      }

      sprintf(selectedItemName, "%s%s", (item == selectedMenuItem ? "> " : "  "), itemName);
      display.drawStr(0, 14 + item * 10, selectedItemName);
    }

    DateTime now = rtc.now();
    sprintf(timeString, "%02d:%02d", now.hour(), now.minute());
    display.drawStr(SCREEN_WIDTH - display.getStrWidth(timeString), SCREEN_HEIGHT - 2, timeString);
  } while (display.nextPage());
}

void handleMenuInput() {
  if (appState != STATE_MENU) {
    return;
  }

  static int32_t before = 0;
  const int32_t now = millis();

  if (now - lastMenuRefresh >= MENU_REFRESH_INTERVAL) {
    lastMenuRefresh = now;
    showMenu();
  }

  if (now - before < DEBOUNCE_DELAY) {
    return;
  }

  if (digitalRead(BUTTON_UP) == LOW) {
    before = now;

    if (selectedMenuItem > 0) {
      selectedMenuItem = static_cast<MenuItem>(selectedMenuItem - 1);
      showMenu();
    }
  }

  if (digitalRead(BUTTON_DOWN) == LOW) {
    before = now;

    if (selectedMenuItem < MENU_COUNT - 1) {
      selectedMenuItem = static_cast<MenuItem>(selectedMenuItem + 1);
      showMenu();
    }
  }

  if (digitalRead(BUTTON_SUPPORT) == LOW) {
    before = now;

    switch (static_cast<uint8_t>(selectedMenuItem)) {
    case MENU_START:
      appState = STATE_PLAYING;
      initGame();
      return;

    case MENU_SCORES:
      appState = STATE_SCORES;
      loadScores();
      showScores();
      return;

    case MENU_SETTINGS:
      appState = STATE_SETTINGS;
      showSettings();
      return;
    }
  }
}
