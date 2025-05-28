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
    int32_t elapsed = now - lastLedUpdate;
    int32_t brightness = 0;

    if (elapsed >= FLASH_GREEN_DURATION) {
      setLed(0, 0, 0);
      currentEffect = NONE;
      return;
    }

    if (elapsed < FLASH_GREEN_DURATION / 2) {
      brightness = map(elapsed, 0, 500, 0, 255);
    } else {
      brightness = map(elapsed, 500, 1000, 255, 0);
    }

    setLed(0, brightness, 0);
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
