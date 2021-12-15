#include "card.h"
Card::Card() : rank{NORANK}, suit{NOSUIT} {}
Card::Card(Rank r, Suit s) : rank{r}, suit{s} {}

void Card::setRank(Rank r){
  rank = r;
}

void Card::setSuit(Suit s){
  suit = s;
}
  
Rank Card::getRank(){
  return rank;
}
Suit Card::getSuit(){
  return suit;
}

std::string Card::cardToString() {
  std::string str = "";
  char cRank;
  if (rank <= 9 && rank >= 2) {
    cRank = '0' + rank;
  } else {
    switch(rank) {
      case 1:
        cRank = 'A';
        break;
      case 10:
        cRank = 'T';
        break;
      case 11:
        cRank = 'J';
        break;
      case 12:
        cRank = 'Q';
        break;
      case 13:
        cRank = 'K';
        break;
      case 0:
        cRank = '0';
        break;
    }
  }
  str += cRank;
  char cSuit;
  switch(suit) {
    case 1:
      cSuit = 'D';
      break;
    case 2:
      cSuit = 'C';
      break;
    case 3:
      cSuit = 'H';
      break;
    case 4:
      cSuit = 'S';
      break;  
  }
    str += cSuit;
  return str;
}

