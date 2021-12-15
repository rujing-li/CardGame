#include "computerstrategy.h"

int ComputerStrategy::playerTurnAlgrm(Player * player, Table & table, Deck & deck){
  if (player->canPlay(deck)) {
    std::vector<int> lPlays = player->legalPlays(table, deck);
    player->playCard(table, deck, lPlays[0]);
  } else {
    player->discardCard(player->handFrontCard());
  }
  return 0;
}

ComputerStrategy::~ComputerStrategy() {}