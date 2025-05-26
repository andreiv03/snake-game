#include "scores.hpp"

SdFat sd;
SdFile file;

ScoreEntry savedScores[MAX_SCORES];
uint8_t scoreCount = MAX_SCORES;
uint8_t selectedScoreIndex = 0;

uint8_t getScoreListLength() { return scoreCount + 1; }

void saveScore(const ScoreEntry &entry) {
  if (!file.open(SCORES_FILENAME, O_WRITE | O_CREAT | O_APPEND)) {
    return;
  }

  file.write((const uint8_t *)&entry, sizeof(ScoreEntry));
  file.close();
}

void loadScores() {
  scoreCount = 0;

  if (!file.open(SCORES_FILENAME, O_READ)) {
    return;
  }

  uint32_t fileSize = file.fileSize();
  uint32_t totalEntries = fileSize / sizeof(ScoreEntry);
  uint32_t entriesToSkip = totalEntries > MAX_SCORES ? totalEntries - MAX_SCORES : 0;
  file.seekSet(entriesToSkip * sizeof(ScoreEntry));

  while (file.available() && scoreCount < MAX_SCORES) {
    ScoreEntry entry;

    if (file.read((uint8_t *)&entry, sizeof(ScoreEntry)) == sizeof(ScoreEntry)) {
      savedScores[scoreCount++] = entry;
    } else {
      break;
    }
  }

  file.close();
}

void showScores() {
  display.firstPage();
  display.setFont(u8g2_font_profont11_tr);

  char item[16];
  char selectedItem[16];

  uint8_t listLength = getScoreListLength();
  uint8_t firstVisible = selectedScoreIndex;

  if (selectedScoreIndex > listLength - MAX_VISIBLE_SCORES) {
    firstVisible = listLength > MAX_VISIBLE_SCORES ? listLength - MAX_VISIBLE_SCORES : 0;
  }

  do {
    display.drawStr(0, 10, "Scores");

    for (uint8_t index = 0; index < MAX_VISIBLE_SCORES; index++) {
      uint8_t firstVisibleIndex = firstVisible + index;

      if (firstVisibleIndex >= listLength) {
        break;
      }

      if (firstVisibleIndex == scoreCount) {
        sprintf(item, "Back");
      } else {
        ScoreEntry entry = savedScores[firstVisibleIndex];
        sprintf(item, "%d, %02d:%02d", entry.score, entry.hours, entry.minutes);
      }

      sprintf(selectedItem, "%s%s", (firstVisibleIndex == selectedScoreIndex ? "> " : "  "), item);
      display.drawStr(0, 24 + index * 10, selectedItem);
    }
  } while (display.nextPage());
}

void handleScoresInput() {
  if (appState != STATE_SCORES) {
    return;
  }

  static int32_t before = 0;
  const int32_t now = millis();

  if (now - before < DEBOUNCE_DELAY) {
    return;
  }

  if (digitalRead(BUTTON_UP) == LOW) {
    before = now;

    if (selectedScoreIndex > 0) {
      selectedScoreIndex--;
      showScores();
    }
  }

  if (digitalRead(BUTTON_DOWN) == LOW) {
    before = now;

    if (selectedScoreIndex < getScoreListLength() - 1) {
      selectedScoreIndex++;
      showScores();
    }
  }

  if (digitalRead(BUTTON_SUPPORT) == LOW) {
    before = now;

    if (selectedScoreIndex == scoreCount) {
      selectedScoreIndex = 0;
      selectedMenuItem = MENU_START;
      appState = STATE_MENU;
      showMenu();

      while (digitalRead(BUTTON_SUPPORT) == LOW) {
        delay(10);
      }
    }
  }
}
