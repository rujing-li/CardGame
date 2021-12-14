#include <deque>
#include <vector>
#include <iostream>

class Deck;
class Table {
  std::vector<std::deque<int>> fourSuits;
 public:
  Table();
  bool addCardToTable(Deck * deck, int cardId);
  std::vector<int> potentialLegalPlays(Deck * deck);
  std::ostream & printTable(Deck * deck, std::ostream & out);
};