#pragma once

#include "main.hpp"
#include <Arduino.h>

#define GAME_OFFSET_Y 16

#define SNAKE_MAX_LENGTH 10
#define SNAKE_SIZE 4
#define SNAKE_SPEED 100

#define WINNING_SCORE 5
#define TIME_LIMIT 30

enum Direction { DIRECTION_RIGHT, DIRECTION_LEFT, DIRECTION_UP, DIRECTION_DOWN };

struct Game {
  uint8_t score;
  uint32_t startTime;
};

struct Snake {
  int16_t x;
  int16_t y;
  uint8_t length;
  int16_t bodyX[SNAKE_MAX_LENGTH];
  int16_t bodyY[SNAKE_MAX_LENGTH];
  Direction direction = DIRECTION_RIGHT;
};

struct Point {
  int16_t x;
  int16_t y;
};

void initGame();

void handleDirectionInput();

void moveSnake();

bool isOutOfBounds(int16_t x, int16_t y);

void wrapAroundScreen();

void onPointEaten();

bool isTimeUp();

bool isSelfCollision();

void endGame(const char *message);

void spawnPoint();

void updateGame();

void drawGame();
