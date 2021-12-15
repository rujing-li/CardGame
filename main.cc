#include "card.h"
#include "deck.h"
#include "table.h"
#include <iostream>
#include <vector>
int main() {
  Card card;
  Card card2(THREE, SPADE);
  Deck deck(20840325);
  deck.printDeck(std::cout);
  std::cout << std::endl;
  deck.shuffle();
  deck.printDeck(std::cout);
  card = deck.getCard(34);
  std::cout << card.cardToString() << std::endl; 
  std::cout << deck.whoHas7S() << std::endl;
  // Table table;
  // table.printTable(&deck, std::cout);
  // int temp;
  // while (std::cin >> temp) {
  //   table.addCardToTable(&deck, temp);
  //   table.printTable(&deck, std::cout);
  // }
  // std::vector<int> pLegalPlays = table.potentialLegalPlays(&deck);
  // for (auto it: pLegalPlays) std::cout << deck.getCard(it).cardToString() << " ";
  // std::cout << std::endl;

  
}