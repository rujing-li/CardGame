#include "computerstrategy.h"
#include "deck.h"
#include "table.h"
#include "player.h"
int ComputerStrategy::playerTurnAlgrm(Player * player, Table & table, Deck & deck){
  if (player->canPlay(table, deck)) {
    std::vector<int> lPlays = player->legalPlays(table, deck);
    player->playCard(table, deck, lPlays[0]);
  } else {
    player->discardCard(table, deck, player->handFrontCard());
  }
  return 0;
}

ComputerStrategy::~ComputerStrategy() {}