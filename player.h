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
  void changeStrategy(std::shared_ptr<Strategy> strg);
 public:
  Player(int playerNum, PType pType);
  bool playerTurn(Table & table, Deck & deck);
  int score(Deck & deck);
  std::vector<int> legalPlays(Table & table, Deck & deck);
  std::ostream & printHand(Deck & deck, std::ostream & out);
  std::ostream & printLPlays(Table & table, Deck & deck, std::ostream & out);
  bool canPlay(Table & table, Deck & deck);
  bool playCard(Table & table, Deck & deck, int cardId);
  bool discardCard(Table & table, Deck & deck, int cardId);
  int handFrontCard();
  void clearDiscards();
  void dealHand();
};
#endif