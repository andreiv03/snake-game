#pragma once

#include "main.hpp"
#include <Arduino.h>
#include <SdFat.h>

#define MAX_SCORES 10
#define MAX_VISIBLE_SCORES 5
#define SCORES_FILENAME "scores.txt"

struct ScoreEntry {
  uint8_t score;
  uint8_t hours;
  uint8_t minutes;
};

extern SdFat sd;
extern SdFile file;

extern ScoreEntry savedScores[MAX_SCORES];
extern uint8_t scoreCount;
extern uint8_t selectedScoreIndex;

uint8_t getScoreListLength();

void saveScore(const ScoreEntry &entry);

void loadScores();

void showScores();

void handleScoresInput();
