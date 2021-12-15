#include "humanstrategy.h"

int HumanStrategy::playerTurnAlgrm(Player * player, Table & table, Deck & deck) {
  while(true) {
    std::string command;
    std::cin >> command;
    if (command == "quit") { 
      return 1;
    } else if (command == "ragequit"){
      return 2;
    } else if (command == "deck"){
      deck.printDeck(std::cout);
    } else if (command == "play"){
      std::string cStr;
      std::cin >> cStr;
      Card card;
      if (strToCard(cStr, card)) {
        continue;
      }      
      if (player->playCard(table, deck, deck.getId(card.rank, card.suit))) { 
        continue;
      }
      return 0;
    } else if (command == "discard"){
      std::string cStr;
      std::cin >> cStr;
      Card card;
      if (strToCard(cStr, card)) {
        continue;
      }      
      if (player->discardCard(deck.getId(card.rank, card.suit))) {
        std::cout << "Try again." << std::endl;
        continue;
      }
      return 0;
    } else {
      std::cout << "Wrong command. Try again." << std::endl;
    }
}

HumanStrategy::~HumanStrategy() {}

bool strToCard(std::string str, Card & card) {
  char rank = str[0];
  char suit = str[1];
  Card card;
  if (rank <= '9' && rank >= '2') {
    card.setRank(static_cast<Rank>(rank - '0'));
  } else {
    switch(rank) {
      case 'A':
        card.setRank(ACE);
        break;
      case 'T':
        card.setRank(TEN);
        break;
      case 'J':
        card.setRank(JACK);
        break;
      case 'Q':
        card.setRank(QUEEN);
        break;
      case 'K':
        card.setRank(KING);
        break;
      default:
        std::cout << "Invalid Rank. Try Again." << std::endl;
        return true;
    }
  }
  switch(suit) {
    case 'D':
      card.setSuit(DIAMOND);
      break;
    case 'C':
      card.setSuit(CLUB);
      break;
    case 'H':
      card.setSuit(HEART);
      break;
    case 'S':
      card.setSuit(SPADE);
      break;  
    default:
      std::cout << "Invalid Rank. Try Again. " << std::endl;
      return true;
  }
}

