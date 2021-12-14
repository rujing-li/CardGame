#ifndef DECK_H
#define DECK_H
#include "card.h"
#include <vector>
#include <random>
#include <memory>
class Deck {
  std::vector<std::unique_ptr<Card>> deck;
  std::default_random_engine rng;
 public:
  Deck(int seed);
  void shuffle();
  Card getCard(int id);
  int getId(Rank rank, Suit suit);
  std::ostream & printDeck(std::ostream & out);
};
#endif