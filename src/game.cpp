#include "game.hpp"

Game game;
Snake snake;
Point point;

void initGame() {
  game.startTime = millis();
  game.score = 0;

  snake.x = 0;
  snake.y = GAME_OFFSET_Y;
  snake.length = 1;
  snake.bodyX[0] = snake.x;
  snake.bodyY[0] = snake.y;
  snake.direction = DIRECTION_RIGHT;

  spawnPoint();
}

void handleDirectionInput() {
  if (digitalRead(BUTTON_UP) == LOW && snake.direction != DIRECTION_DOWN) {
    snake.direction = DIRECTION_UP;
  } else if (digitalRead(BUTTON_LEFT) == LOW && snake.direction != DIRECTION_RIGHT) {
    snake.direction = DIRECTION_LEFT;
  } else if (digitalRead(BUTTON_DOWN) == LOW && snake.direction != DIRECTION_UP) {
    snake.direction = DIRECTION_DOWN;
  } else if (digitalRead(BUTTON_RIGHT) == LOW && snake.direction != DIRECTION_LEFT) {
    snake.direction = DIRECTION_RIGHT;
  }
}

void moveSnake() {
  for (uint8_t index = snake.length - 1; index > 0; index--) {
    snake.bodyX[index] = snake.bodyX[index - 1];
    snake.bodyY[index] = snake.bodyY[index - 1];
  }

  snake.bodyX[0] = snake.x;
  snake.bodyY[0] = snake.y;

  switch (snake.direction) {
  case DIRECTION_UP:
    snake.y -= SNAKE_SIZE;
    break;

  case DIRECTION_LEFT:
    snake.x -= SNAKE_SIZE;
    break;

  case DIRECTION_DOWN:
    snake.y += SNAKE_SIZE;
    break;

  case DIRECTION_RIGHT:
    snake.x += SNAKE_SIZE;
    break;

  default:
    break;
  }
}

bool isOutOfBounds(int16_t x, int16_t y) {
  return x < 0 || x >= SCREEN_WIDTH || y < GAME_OFFSET_Y || y >= SCREEN_HEIGHT;
}

void wrapAroundScreen() {
  if (snake.x >= SCREEN_WIDTH) {
    snake.x = 0;
  }

  if (snake.x < 0) {
    snake.x = SCREEN_WIDTH - SNAKE_SIZE;
  }

  if (snake.y >= SCREEN_HEIGHT) {
    snake.y = GAME_OFFSET_Y;
  }

  if (snake.y < GAME_OFFSET_Y) {
    snake.y = SCREEN_HEIGHT - SNAKE_SIZE;
  }
}

void onPointEaten() {
  game.score++;

  if (game.score >= WINNING_SCORE) {
    endGame("You Win!");
    return;
  }

  if (snake.length < SNAKE_MAX_LENGTH) {
    snake.length++;
  }

  flashGreen();
  spawnPoint();
}

bool isTimeUp() {
  uint32_t elapsed = (millis() - game.startTime) / 1000;
  return elapsed >= TIME_LIMIT;
}

bool isSelfCollision() {
  for (uint8_t index = 1; index < snake.length; index++) {
    if (snake.x == snake.bodyX[index] && snake.y == snake.bodyY[index]) {
      return true;
    }
  }

  return false;
}

void endGame(const char *message) {
  DateTime now = rtc.now();

  ScoreEntry entry;
  entry.score = game.score;
  entry.hours = now.hour();
  entry.minutes = now.minute();

  saveScore(entry);
  showEndScreen(game.score, message);
  appState = STATE_MENU;
  initGame();
  showMenu();
}

void updateGame() {
  handleDirectionInput();
  moveSnake();

  if (settings.collisions) {
    if (isOutOfBounds(snake.x, snake.y)) {
      endGame("Game Over!");
      return;
    }
  } else {
    wrapAroundScreen();
  }

  if (snake.x == point.x && snake.y == point.y) {
    onPointEaten();
    updateLed();
    return;
  }

  if (isTimeUp()) {
    endGame("Time's Up!");
    return;
  }

  if (isSelfCollision()) {
    endGame("Game Over!");
    return;
  }

  updateLed();
}

void drawGame() {
  display.firstPage();
  char buffer[16];

  do {
    display.drawHLine(0, GAME_OFFSET_Y - 1, SCREEN_WIDTH);
    display.setFont(u8g2_font_profont11_tr);

    sprintf(buffer, "Score: %d", game.score);
    display.drawStr(0, 10, buffer);

    uint32_t elapsed = (millis() - game.startTime) / 1000;
    int32_t remaining = TIME_LIMIT - elapsed;

    if (remaining < 0) {
      remaining = 0;
    }

    sprintf(buffer, "Time: %ld", remaining);
    display.drawStr(SCREEN_WIDTH - display.getStrWidth(buffer), 10, buffer);

    for (uint8_t index = 0; index < snake.length; index++) {
      display.drawBox(snake.bodyX[index], snake.bodyY[index], SNAKE_SIZE, SNAKE_SIZE);
    }

    display.drawFrame(point.x, point.y, SNAKE_SIZE, SNAKE_SIZE);
  } while (display.nextPage());
}

void spawnPoint() {
  do {
    point.x = (rand() % (SCREEN_WIDTH / SNAKE_SIZE)) * SNAKE_SIZE;
    point.y = (rand() % (SCREEN_HEIGHT / SNAKE_SIZE)) * SNAKE_SIZE;
  } while (point.y < GAME_OFFSET_Y);
}
