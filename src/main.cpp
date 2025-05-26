#include "main.hpp"

AppState appState = STATE_MENU;

void setup() {
  Wire.begin();

  if (!sd.begin()) {
    return;
  }

  initDisplay();
  initRTC();
  initLed();
  initSettings();

  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_SUPPORT, INPUT_PULLUP);
  pinMode(LED_GREEN_PIN, OUTPUT);

  showLoadingScreen();
  showMenu();
}

void loop() {
  switch (static_cast<uint8_t>(appState)) {
  case STATE_MENU:
    handleMenuInput();
    break;

  case STATE_PLAYING:
    updateGame();

    if (appState == STATE_PLAYING) {
      drawGame();
    }

    delay(SNAKE_SPEED);
    break;

  case STATE_SCORES:
    handleScoresInput();
    break;

  case STATE_SETTINGS:
    handleSettingsInput();
    break;

  default:
    break;
  }
}
