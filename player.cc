#include "player.h"
#include <iostream>

Player::Player(int playerNum, PType pType) : playerNum{playerNum} {
  if (pType == COMPUTER) { 
    strategy = std::make_shared<ComputerStrategy>();
  } else if (pType == HUMAN) {
    strategy = std::make_shared<HumanStrategy>();
  }
}

bool Player::canPlay(Deck & deck) {
  std::vector<int> vec = legalPlays(deck);
  return (vec.size() != 0);
}

bool Player::playCard(Table & table, Deck & deck, int cardId) {

  std::vector<int> lPlays = legalPlays(table, deck);
  for (auto it: lPlays) {
    if (it == cardId) {
      // add to table
      table.addCardToTable(deck, cardId);
      // search in hand for the card to be played
      auto that = hand.begin();
      while (that != hand.end()) {
        if ((*that) == cardId) {
          // erase from hand
          that = hand.erase(that);
          std::cout << "Player " << playerNum << "plays " << deck.getCard(cardId).cardToString() << "." << std::endl;  
          return false;
        } else {
          ++it;
        }
      }
      std::cout << "Logic Error." << std::endl;
      return true;
    }
  }
  std::cout << "This is not a legal play." << std::endl;
  return true;
}

bool Player::discardCard(int cardId) {
  // verify condition to discard
  if (canPlay()) {
    std::cout << "You have a legal play. You may not discard." << std::endl;
    return true;
  }
  // search in hand for the card to be discarded
  auto it = hand.begin();
  while (it != hand.end()) {
    if ((*it) == cardId) {
      // erase from hand
      it = hand.erase(it);
      // add to discards
      discards.push_back(cardId);
      return false;
    } else {
      ++it;
    }
  }
  return true;
}

int Player::handFrontCard() {
  return hand[0];
}

void Player::changeStrategy(std::shared_ptr<Strategy> strg) {
  strategy = strg;
}

std::iostream & printHand(Deck & deck, std::iostream & out){
  std::cout << "Your Hand:";
  for (int cardId: hand) {
    std::cout << deck.getCard(deck, cardId).cardToString() << " ";
  }
  std::cout << std::endl;
}

std::iostream & printLPlays(Table & table, Deck & deck, std::iostream & out){
  std::cout << "Legal Plays:";
  vector<int> lPlays = legalPlays(table, deck);
  for (int cardId: lPlays) {
    std::cout << deck.getCard(deck, cardId).cardToString() << " ";
  }
  std::cout << std::endl;
}

bool Player::playerTurn(Table & table, Deck & deck) {
  printHand(deck, std::cout);
  printLPlays(deck, std::cout);

  int code = strategy->playerTurnAlgrm(this, table, deck);
  if (code == 2) {
    std::cout << "Player " << playerNum << " ragequits. A computer will now take over."
    changeStrategy(std::make_shared<ComputerStrategy>());
    strategy->playerTurnAlgrm(this, table, deck);
  } else if (code == 1) {
    return true; // terminate program
  } else {
    assert(code == 0);
    return false;
  }
}

void Player::score() {
  int score = 0;
  for (auto it: discards) {
    score += it;
  }
  return score;
}

std::vector<int> Player::legalPlays(Table & table, Deck & deck){
  std::vector<int> ret;
  std::vector<int> vec = table.potentialLegalPlays(deck);
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