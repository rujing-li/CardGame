#include "game.h"
#include <climits>

Game::Game(int seed): deck{Deck(seed)}, table{Table()} {
  for (int i{0}; i < 4; i++) {
    PType pType;
    char type;
    std::cout << "Is Player " << i + 1 << " a human (h) or a computer (c)?" << std::endl;
    std::cin >> type;
    if (type == 'c') pType = COMPUTER;
    if (type == 'h') pType = HUMAN;
    players.push_back(std::make_unique<Player>(i + 1, pType));
    scores.push_back(0);
  }
}

bool Game::gameOver() {
  for (int i{0}; i < 4; i++) {
    Player * player = players[i].get();
    if (player->score() >= 80) {
      return true;
    }
  }
  return false;
}

bool Game::startRound() {
  // suffle deck and deal cards
  deck.shuffle();
  for (int i{0}; i < 4; ++i) {
    // players[i].get()->dealHand(deck.dealCards(i));
    players[i].get()->dealHand();
  }
  // start Round
  // determine who has 7S
  int whichPlayer = deck.whoHas7S();
  std::cout << "A new round begins. It’s Player" << whichPlayer + 1 << "’s turn to play." << std::endl;
  for (int i{0}; i < 52; i++) {
    table.printTable(deck, std::cout);
    if (players[whichPlayer % 4].get()->playerTurn(table, deck)){
      return true;
    } 
    whichPlayer++;
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
  while(!gameOver()) {
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
    if (scores[i] == minScore) {
      std::cout << "Player" << (i + 1) << " wins!" << std::endl;
    }
  }
}
