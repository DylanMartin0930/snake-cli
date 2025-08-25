#include "../include/game.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

Game::Game()
    : snake(width / 2, height / 2), // construct Snake at center
      food{rand() % width, rand() % height}, isGameOver(false), playerScore(0) {
}

void Game::Init() {
  isGameOver = false;
  snake.sDir = Snake::STOP;
  snake.tailLength = 0;
  playerScore = 0;

  // reset snake to center
  snake.reset(width / 2, height / 2);

  // respawn food randomly
  food.x = rand() % width;
  food.y = rand() % height;
}

void Game::GameRender(std::string playerName) {
  // top wall
  for (int i = 0; i < width + 2; i++) {
    cout << "-";
  }
  cout << endl;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j <= width; j++) {

      // side walls
      if (j == 0 || j == width) {
        cout << "|";
      }
      // snakes head
      if (i == snake.y && j == snake.x) {
        cout << "O";
      }
      // Food
      else if (i == food.y && j == food.x) {
        cout << "#";
      }
      // Snake Tail
      /* note here we are checking if the current cell is apart of the snails
         tail or not. using snakeTailX/Y arrays to check whether the
         corresponding cell should be a tail
         */
      else {
        bool isTail = false;
        for (int k = 0; k < snake.tailLength; k++) {
          if (snake.snakeTailX[k] == j && snake.snakeTailY[k] == i) {
            cout << "o";
            isTail = true;
          }
        }
        if (!isTail) {
          cout << " ";
        }
      }
    }
    cout << std::endl;
  }

  // bottom wall
  for (int i = 0; i < width + 2; i++) {
    cout << "-";
  }
  cout << endl;

  // display player score;
  cout << playerName << "'s Score: " << playerScore << endl;
}

void Game::ClearScreen() { cout << "\033[2J\033[1;1H"; }

void Game::UpdateGame() {
  int prevX = snake.snakeTailX[0];
  int prevY = snake.snakeTailY[0];
  int prev2X, prev2Y;

  // update starting position of tail
  snake.snakeTailX[0] = snake.x;
  snake.snakeTailY[0] = snake.y;

  // update rest of tail [ everyting after its starting segment]
  for (int i = 1; i < snake.tailLength; i++) {
    // get the NEXT Tail segment [after snakeTail[0] ]
    prev2X = snake.snakeTailX[i];
    prev2Y = snake.snakeTailY[i];

    // update the current segment to the previous position
    snake.snakeTailX[i] = prevX;
    snake.snakeTailY[i] = prevY;

    // update the previous segment to the next
    prevX = prev2X;
    prevY = prev2Y;
  }

  // handle directions
  switch (snake.sDir) {
  case Snake::LEFT:
    snake.x--;
    break;
  case Snake::RIGHT:
    snake.x++;
    break;
  case Snake::UP:
    snake.y--;
    break;
  case Snake::DOWN:
    snake.y++;
    break;
  }

  // checks for snake collision with wall:
  if (snake.x >= width || snake.x < 0 || snake.y > height || snake.y < 0) {
    isGameOver = true;
  }

  // checks for collision with tail (o)
  for (int i = 0; i < snake.tailLength; i++) {
    if (snake.x == snake.snakeTailX[i] && snake.y == snake.snakeTailY[i]) {
      isGameOver = true;
    }
  }

  // checks for snake colision with food (#)
  if (snake.x == food.x && snake.y == food.y) {
    playerScore += 10;
    // reset food position
    food.x = rand() % width;
    food.y = rand() % height;
    // update snake;
    snake.tailLength++;
  }
}

int Game::SetDifficulty() {
  int dfc, choice;
  cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard "
          "\nNOTE: if not chosen or pressed any other "
          "key, the difficulty will be automatically set "
          "to medium\nChoose difficulty level: ";
  cin >> choice;

  switch (choice) {
  case '1':
    dfc = 50;
    break;
  case '2':
    dfc = 100;
    break;
  case '3':
    dfc = 150;
    break;
  default:
    dfc = 100;
  }
  return dfc;
}

// SETUP KEYBOARD INPUTS
bool kbhit() {
  struct timeval tv = {0, 0};
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  return select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv) > 0;
}

char getch() {
  char c;
  if (read(STDIN_FILENO, &c, 1) < 0)
    return 0;
  return c;
}

void Game::UserInput() {
  if (kbhit()) {
    char key = getch();
    switch (key) {
    case 'a':
      snake.sDir = Snake::LEFT;
      break;
    case 'd':
      snake.sDir = Snake::RIGHT;
      break;
    case 'w':
      snake.sDir = Snake::UP;
      break;
    case 's':
      snake.sDir = Snake::DOWN;
      break;
    case 'x':
      isGameOver = true;
      break;
    }
  }
}
