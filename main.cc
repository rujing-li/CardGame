#include "card.h"
#include "deck.h"
#include <iostream>
int main() {
  Card card;
  Card card2(THREE, SPADE);
  Deck deck(20840325);
  deck.printDeck(std::cout);
  deck.shuffle();
  deck.printDeck(std::cout);
  card = deck.getCard(34);
  std::cout << card.cardToString() << std::endl; 
}