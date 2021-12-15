#ifndef STRATEGY_H
#define STRATEGY_H
class Player;
class Table;
class Deck;
class Card;
class Strategy {
 public:
  // exit code (0:good, 1:terminate program, 
  //  2:change to computer player(only human player sends this))
  virtual int playerTurnAlgrm(Player * player, Table & table, Deck & deck) = 0;
  virtual ~Strategy();
};
#endif