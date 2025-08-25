#include "include/game.h"
#include <iostream>
#include <string>
#include <unistd.h>

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

struct termios orig_termios;

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig_termios); // save original settings
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON); // disable echo and canonical mode
  raw.c_cc[VMIN] = 0;              // read returns immediately
  raw.c_cc[VTIME] = 0;             // no timeout
  tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios); // restore original
}

int main() {
  Game game;

  std::string playerName;
  cout << "Enter your name: ";
  cin >> playerName;
  int dfc = game.SetDifficulty();
  enableRawMode();

  game.Init();

  while (!game.isGameOver) {

    game.ClearScreen();
    game.GameRender(playerName);
    game.UserInput();
    game.UpdateGame();
    // delay based on difficulty
    cout << "\ngame is running\n";
    usleep(dfc * 1000);
  }
  disableRawMode();
  return 0;
}
