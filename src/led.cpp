#include "led.hpp"

LedEffect currentEffect = NONE;
int32_t lastLedUpdate = 0;

void initLed() {
  pinMode(LED_GREEN_PIN, OUTPUT);
  setLed(0, 0, 0);
}

void setLed(uint8_t r, uint8_t g, uint8_t b) {
  (void)r;
  analogWrite(LED_GREEN_PIN, g);
  (void)b;
}

void updateLed() {
  const int32_t now = millis();

  switch (currentEffect) {
  case FLASH_GREEN:
    if (now - lastLedUpdate > FLASH_GREEN_DURATION) {
      setLed(0, 0, 0);
      currentEffect = NONE;
    } else {
      setLed(0, 255, 0);
    }

    break;

  case NONE:
  default:
    break;
  }
}

void flashGreen() {
  currentEffect = FLASH_GREEN;
  lastLedUpdate = millis();
}
