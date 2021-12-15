#ifndef COMPUTERSTRATEGY_H
#define COMPUTERSTRATEGY_H
class ComputerStrategy : public Strategy {
 public:
  int playerTurnAlgrm(Player * player, Table & table, Deck & deck) override;
  ~ComputerStrategy();
};
#endif