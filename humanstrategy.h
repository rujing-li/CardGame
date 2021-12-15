#ifndef HUMANSTRATEGY_H
#define HUMANSTRATEGY_H
class HumanStrategy : public Strategy {
 public:
  int playerTurnAlgrm(Player * player, Table & table, Deck & deck) override;
  ~HumanStrategy();
};
#endif