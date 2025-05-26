#include "display.hpp"

U8G2_SSD1306_128X64_NONAME_1_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

void initDisplay() {
  display.begin();
  display.clearBuffer();
}

void showLoadingScreen() {
  display.clearBuffer();

  const char *message = "SNAKE";
  display.setFont(u8g2_font_profont17_tr);
  int16_t x = (SCREEN_WIDTH - display.getStrWidth(message)) / 2;
  int16_t y = SCREEN_HEIGHT / 2;

  display.firstPage();

  do {
    display.drawStr(x, y, message);
  } while (display.nextPage());

  delay(3000);
}

void showEndScreen(uint8_t score, const char *message) {
  display.clearBuffer();

  char buffer[16];
  sprintf(buffer, "Score: %d", score);

  display.setFont(u8g2_font_profont17_tr);
  int16_t messageX = (SCREEN_WIDTH - display.getStrWidth(message)) / 2;
  int16_t messageY = SCREEN_HEIGHT / 2;

  display.setFont(u8g2_font_profont11_tr);
  int16_t scoreX = (SCREEN_WIDTH - display.getStrWidth(buffer)) / 2;
  int16_t scoreY = (SCREEN_HEIGHT + 32) / 2;

  display.firstPage();

  do {
    display.setFont(u8g2_font_profont17_tr);
    display.drawStr(messageX, messageY, message);

    display.setFont(u8g2_font_profont11_tr);
    display.drawStr(scoreX, scoreY, buffer);
  } while (display.nextPage());

  delay(3000);
}
