#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "strategy.h"
#include "deck.h"
#include "table.h"
#include <memory>
#include <iostream>

enum PType{ COMPUTER, HUMAN };

class Player {
  int playerNum;
  std::vector<int> hand;
  std::vector<int> discards;
  std::shared_ptr<Strategy> strategy;
  bool canPlay(Deck & deck);
  bool playCard(Table & table, Deck & deck, int cardId);
  bool discardCard(int cardId);
  int handFrontCard();
  void changeStrategy(std::shared_ptr<Strategy> strg);
  std::ostream & printHand(Deck & deck, std::ostream & out);
  std::ostream & printLPlays(Table & table, Deck & deck, std::ostream & out);
 public:
  Player(int playerNum, PType pType);
  bool playerTurn(Table & table, Deck & deck);
  int score();
  std::vector<int> legalPlays(Table & table, Deck & deck);
  void clearDiscards();
  void dealHand(vector<int> cards);
};
#endif