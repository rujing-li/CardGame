#include "deck.h"
#include <algorithm>
#include <iostream>
#include <memory>

Deck::Deck(int seed): rng{std::default_random_engine(seed)} {
  for (int i{1}; i <= 4; i++) {
    for (int j{1}; j <= 13; j++) {
      deck.push_back(std::make_unique<Card>(static_cast<Rank>(j), static_cast<Suit>(i)));
    }
  }
}

void Deck::shuffle() {
  std::shuffle( deck.begin(), deck.end(), rng );
}

Card Deck::getCard(int id) {
  Card card;
  // int r = id % 13;
  // card.setRank(static_cast<Rank>(r));
  // card.setSuit(static_cast<Suit>(((id - r) / 13) + 1));
  card.setRank(deck[id].get()->getRank());
  card.setSuit(deck[id].get()->getSuit());
  return card;
}

int Deck::getId(Rank rank, Suit suit){
  // return rank + (suit - 1) * 13;
  for (int i{0}; i < 52; i++) {
    if (rank == deck[i].get()->getRank()) {
      if (suit == deck[i].get()->getSuit()) {
        return i;
      }
    }
  }
  std::cout << "Wrong rank and/or suit!" << std::endl;
  return -1;
}

std::ostream & Deck::printDeck(std::ostream & out) {
  for (int i{0}; i < 4; i++) {
    for (int j{0}; j < 12; j++) {
      Card * ptr = deck[j + i * 13].get();
      std::string str = ptr->cardToString();
      out << str << " ";
    }
    out << deck[12 + i * 13].get()->cardToString() << "\n";
  }
  return out;
}

int Deck::whoHas7S() {
  for (int i{0}; i < 52; i++) {
    if (SEVEN == deck[i].get()->getRank()) {
      if (SPADE == deck[i].get()->getSuit()) {
        return (i / 13);
      }
    }
  }
}