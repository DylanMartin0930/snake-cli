#include "../include/snake.h"

Snake::Snake(int startX, int startY) { reset(startX, startY); }

void Snake::reset(int startX, int startY) {
  x = startX;
  y = startY;
  tailLength = 0;
  sDir = STOP;

  // clear all tail coordinates
  for (int i = 0; i < maxLength; i++) {
    snakeTailX[i] = 0;
    snakeTailY[i] = 0;
  }
}
