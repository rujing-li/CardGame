#include "player.h"
#include <iostream>

Player::canPlay() {

}

bool Player::discardCard(int cardId) {
  // verify condition to discard
  if (canPlay()) {
    std::cout << "This player cannot discard card." << std::endl;
    return false;
  }
  // search in hand for the card to be discarded
  auto it = hand.begin();
  while (it != hand.end()) {
    if ((*it) == cardId) {
      // erase from hand
      it = hand.erase(it);
      // add to discards
      discards.push_back(cardId);
      return true;
    } else {
      ++it;
    }
  }
  return false;
}

void Player::playerTurn() {

}

void Player::score() {
  int score = 0;
  for (auto it: discards) {
    score += it;
  }
  return score;
}

std::vector<int> Player::legalPlays(Table & table, Deck & deck){
  vector<int> ret;
  vector<int> vec = table.potentialLegalPlays(deck);
  for (auto i : vec) {
    for (auto j : hand) {
      if (i == j) {
        ret.push_back(i);
      }
    }
  }
  return ret;
}

void clearDiscards() {
  discards.clear();
}

void Player::dealHand(vector<int> cards){
  hand.clear();
  assert(cards.size() == 13);
  hand = cards;
}