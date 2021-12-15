#include "game.h"
#include <climits>

Game::Game(int seed): deck{Deck(seed)}, table{Table()} {
  for (int i{0}; i < 4; i++) {
    PType pType;
    char type;
    std::cout << "Is Player" << i + 1 << " a human (h) or a computer (c)?" << std::endl;
    std::cin >> type;
    if (type == 'c') pType = COMPUTER;
    if (type == 'h') pType = HUMAN;
    players.push_back(std::make_unique<Player>(i + 1, pType));
    scores.push_back(0);
  }
}

bool Game::gameOver() {
  for (int i{0}; i < 4; i++) {
    if (scores[i] >= 80) {
      return true;
    }
  }
  return false;
}

bool Game::startRound() {
  // suffle deck and deal cards
  deck.shuffle();
  for (int i{0}; i < 4; ++i) {
    players[i].get()->dealHand();
  }
  // start Round
  // determine who has 7S
  int whichPlayer = deck.whoHas7S();
  std::cout << "A new round begins. It’s Player" << whichPlayer + 1 << "’s turn to play." << std::endl;

  //first turn
  table.printTable(deck, std::cout);

  players[whichPlayer].get()->printHand(deck, std::cout);
  players[whichPlayer].get()->printLPlays(table, deck, std::cout);
  int cardId = deck.getId(SEVEN, SPADE);
  players[whichPlayer].get()->playCard(table, deck, cardId);
  std::cout << std::endl;
  
  for (int i{1}; i < 52; i++) {
    whichPlayer++;
    table.printTable(deck, std::cout);
    if (players[whichPlayer % 4].get()->playerTurn(table, deck)){
      return true;
    } 
  }
  // Round ends
  // update scores
  for (int i{0}; i < 4; ++i) {
      scores[i] += players[i].get()->score();
  }
  // clear table
  table.clearTable();
  // clear discards in each player
  for (int i{0}; i < 4; ++i) {
    players[i].get()->clearDiscards();
  }
  return false;
}

void Game::startGame() {
  // int counter = 0;
  while(!gameOver()) {
    // std::cout << "Counter: " << counter++ << std::endl;
    if (startRound()) {
      return;
    } 
  }
  // find the min score
  int minScore = INT_MAX;
  for (int i{0}; i < 4; i++) {
    if (scores[i] < minScore) {
      minScore = scores[i];
    }
  }
  // declare winner
  for (int i{0}; i < 4; i++) {
    std::cout << "player "<< i + 1 << "'s score: " << scores[i] << std::endl;
    if (scores[i] == minScore) {
      std::cout << "Player" << (i + 1) << " wins!" << std::endl;
    }
  }
}
