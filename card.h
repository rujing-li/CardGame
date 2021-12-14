#ifndef CARD_H
#define CARD_H
#include <string>
enum Rank { NORANK, ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
  NINE, TEN, JACK, QUEEN, KING };
enum Suit { NOSUIT, DIAMOND, CLUB, HEART, SPADE };

class Card {
  Rank rank;
  Suit suit;
 public:
  Card();
  Card(Rank r, Suit s);
  std::string cardToString();
  void setRank(Rank r);
  void setSuit(Suit s);
  Rank getRank();
  Suit getSuit();
};
#endif