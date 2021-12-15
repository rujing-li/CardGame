#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

enum PType{ COMPUTER, HUMAN };

class Player {
  std::vector<int> hand;
  std::vector<int> discards;
  PType pType;
  bool canPlay();
  bool discardCard(int cardId);
 public:
  void playTurn();
  int score();
  std::vector<int> legalPlays(Deck & deck);
  void clearDiscards();
  void dealHand(vector<int> cards);
};
#endif