#include "player.h"
#include <iostream>
#include <cassert>
#include "computerstrategy.h"
#include "humanstrategy.h"

Player::Player(int playerNum, PType pType) : playerNum{playerNum} {
  if (pType == COMPUTER) { 
    strategy = std::make_shared<ComputerStrategy>();
  } else if (pType == HUMAN) {
    strategy = std::make_shared<HumanStrategy>();
  }
}

void Player::changeStrategy(std::shared_ptr<Strategy> strg) {
  strategy = strg;
}

std::ostream & Player::printHand(Deck & deck, std::ostream & out){
  out << "Your hand: ";
  for (auto cardId: hand) {
    out << deck.getCard(cardId).cardToString() << " ";
  }
  out << "\n";
  return out;
}

std::ostream & Player::printLPlays(Table & table, Deck & deck, std::ostream & out){
  out << "Legal plays: ";
  std::vector<int> lPlays = legalPlays(table, deck);
  for (int cardId: lPlays) {
    out << deck.getCard(cardId).cardToString() << " ";
  }
  out << std::endl;
  return out;
}

bool Player::playerTurn(Table & table, Deck & deck) {
  printHand(deck, std::cout);
  printLPlays(table, deck, std::cout);

  int code = strategy->playerTurnAlgrm(this, table, deck);
  if (code == 2) {
    std::cout << "Player " << playerNum << " ragequits. A computer will now take over.\n";
    changeStrategy(std::make_shared<ComputerStrategy>());
    strategy->playerTurnAlgrm(this, table, deck);
    return false;
  } else if (code == 1) {
    return true; // terminate program
  } else {
    assert(code == 0);
    return false;
  }
}

int Player::updateScore(Deck & deck) {
  int score = 0;
  std::cout << "Player" << playerNum << "'s discards: ";
  for (auto it: discards) {
    Card card = deck.getCard(it);
    std::cout << card.cardToString() << " ";
    score += card.getRank();
  }
  std::cout << std::endl;
  return score;
}

std::vector<int> Player::legalPlays(Table & table, Deck & deck){
  std::vector<int> ret;
  std::vector<int> vec = table.potentialLegalPlays(deck);
  for (auto i : hand) {
    for (auto j : vec) {
      if (i == j) {
        ret.push_back(i);
      }
    }
  }
  return ret;
}

bool Player::canPlay(Table & table, Deck & deck) {
  std::vector<int> vec = legalPlays(table, deck);
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
          std::cout << "Player" << playerNum << " plays " << deck.getCard(cardId).cardToString() << std::endl;  
          std::cout << std::endl;
          return false;
        } else {
          ++that;
        }
      }
      std::cout << "Logic Error." << std::endl;
      return true;
    }
  }
  std::cout << "This is not a legal play." << std::endl;
  return true;
}

bool Player::discardCard(Table & table, Deck & deck, int cardId) {
  // verify condition to discard
  if (canPlay(table, deck)) {
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
      std::cout << "Player" << playerNum << " discards " << deck.getCard(cardId).cardToString() << std::endl;  
      std::cout << std::endl;
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

void Player::clearDiscards() {
  discards.clear();
}

void Player::dealHand(){
  hand.clear();
  std::vector<int> cards;
  for (int i{0}; i < 13; i++) {
    cards.push_back((playerNum - 1) * 13 + i);
  }
  hand = cards;
}
