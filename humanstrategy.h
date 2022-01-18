#ifndef HUMANSTRATEGY_H
#define HUMANSTRATEGY_H
#include <string>
#include "strategy.h"

class HumanStrategy : public Strategy {
 public:
  int playerTurnAlgrm(Player * player, Table & table, Deck & deck) override;
  ~HumanStrategy();
};
bool strToCard(std::string str, Card & card);
#endif
