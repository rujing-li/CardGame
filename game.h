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
  players std::vector<unique_ptr<Player>>;
  scores std::vector<int>;
  void startRound();
  bool gameOver();
 public:
  Game(int seed);
  void startGame();
};
#endif