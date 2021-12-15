#include "table.h"
#include "deck.h"
#include "card.h"
#include <iostream>
#include <cassert>

Table::Table() {
  std::deque<int> clubs, diamonds, hearts, spades;
  fourSuits.push_back(clubs);
  fourSuits.push_back(diamonds);
  fourSuits.push_back(hearts);
  fourSuits.push_back(spades);
}

bool Table::addCardToTable(Deck & deck, int cardId) {
  Card card = deck.getCard(cardId);
  Suit s = card.getSuit();
  Rank r = card.getRank();
  if (s == NOSUIT) {
      std::cout << "No Suit Specified, Add Card cancelled.";
      return false;
  } else {
    std::deque<int> & list = fourSuits[s - 1];
    if (list.empty()) {
      if (r == SEVEN) {
        list.push_back(cardId);
      } else {
        std::cout << "Invalid Play" << std::endl;
        return false;
      }
    } else {
      int front_rank = deck.getCard(list.front()).getRank();
      int back_rank = deck.getCard(list.back()).getRank();
      if ((front_rank - r) == 1) list.push_front(cardId);
      else if ((r - back_rank) == 1) list.push_back(cardId);
      else { 
        std::cout << "Invalid Play" << std::endl; 
        return false; 
      }
    }
    return true;
  }
}

std::vector<int> Table::potentialLegalPlays(Deck & deck) {
  std::vector<int> vec;  
  for (int i = 0; i < 4; i++) {
    std::deque<int> & list = fourSuits[i];
    if (list.empty()) {
      vec.push_back(deck.getId(SEVEN, static_cast<Suit>(i + 1)));
      if (i == (SPADE - 1)) { // if 7S has not been placed, this is the first turn of a round
        vec.clear();
        vec.push_back(deck.getId(SEVEN, SPADE));
        return vec;
      }
    } else {
      int front_rank = deck.getCard(list.front()).getRank();
      int back_rank = deck.getCard(list.back()).getRank();
      assert(front_rank >= 1 && front_rank <= 13);
      assert(back_rank >= 1 && back_rank <= 13);
      if (front_rank != ACE) {
        vec.push_back(deck.getId(static_cast<Rank>(front_rank - 1), static_cast<Suit>(i + 1)));
      }
      if (back_rank != KING) {
        vec.push_back(deck.getId(static_cast<Rank>(back_rank + 1), static_cast<Suit>(i + 1)));
      }      
    }
  }
  return vec;
}

std::ostream & Table::printTable(Deck & deck, std::ostream & out) {
  out << "Cards on the table:\n";
  for (int i{0}; i < 4; i++) {
    std::deque<int> suit = fourSuits[i];
    switch(i) {
      case 0:
        out << "CLUBS: ";
        break;
      case 1:
        out << "DIAMONDS: ";
        break;
      case 2:
        out << "HEARTS: ";
        break;
      case 3:
        out << "SPADES: ";
        break;
    }
    for (auto j: suit) {
      Card card = deck.getCard(j);
      out << card.cardToString() << " ";
    }
    out << "\n";
  }
  return out;
}

void Table::clearTable() {
  for (int i{0}; i < 4; i++) {
    fourSuits[i].clear();
  }
}