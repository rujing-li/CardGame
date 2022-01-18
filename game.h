#ifndef GAME_H
#define GAME_H
#include "deck.h"
#include "table.h"
#include "player.h"
#include <memory>
#include <vector>

class Game {
  Deck deck;
  Table table;
  std::vector<std::unique_ptr<Player>> players;
  std::vector<int> scores;
  // if returns true, terminate the program immediately
  bool startRound();
  bool gameOver();
 public:
  Game(int seed);
  // if returns true, terminate the program immediately
  void startGame();
};
#endif
