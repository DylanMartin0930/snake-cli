#pragma once
#ifndef SNAKE_H
#define SNAKE_H

class Snake {

public:
  // defining upper limits
  // TODO: probaly make this the total number of pixels in the grid
  static const int maxLength = 100;

  int x, y; // head position
  /* here the length of the arrays signal the max length of the snakes tail,
   * where each cell is a POTENTIAL tail segment which will hold the cordinate
   * for its position on the grid */
  int snakeTailX[100], snakeTailY[100];
  int tailLength;

  enum snakeDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
  snakeDirection sDir;

  // constructor
  Snake(int startX, int startY);

  void reset(int startX, int startY);
};

#endif
