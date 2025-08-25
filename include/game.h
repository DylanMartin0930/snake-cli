#pragma once
#include <string>
#ifndef GAME_H
#define GAME_H

#include "food.h"
#include "snake.h"

class Game {

public:
  // game boundaries
  static const int width = 60;
  static const int height = 40;

  // constructor
  Game();

  Snake snake;
  Food food;

  // game state
  bool isGameOver;
  int playerScore;

  void Init();
  void GameRender(std::string playerName);
  void ClearScreen();
  void UpdateGame();
  int SetDifficulty();
  void UserInput();
};

#endif
