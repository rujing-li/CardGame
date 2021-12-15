#include "game.h"
#include <string>

int main(int argc, char * argv[]) {
  int seed = 10;
  if (argc > 1) {
    seed = std::stoi(argv[1]);
  }
  Game game(seed);
  game.startGame();
}