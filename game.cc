#include "game.h"

Game::Game(int seed): deck{Deck(seed)}, table{Table()},
 players{vector<unique_ptr<Player>>}, scores{vector<int>} {
  players.push_back(make_unique<Player>());
  players.push_back(make_unique<Player>());
  players.push_back(make_unique<Player>());
  players.push_back(make_unique<Player>());
  scores.push_back(0);
  scores.push_back(0);
  scores.push_back(0);
  scores.push_back(0);
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
    players[i].get()->dealHand(deck.dealCard(i));
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
      scores[i] += players[i].score();
  }
  // clear table
  table.clearTable();
  // clear discards in each player
  for (int i{0}; i < 4; ++i) {
    players[i].clearDiscards();
  }
  return false;
}

bool Game::startGame() {
  while(!gameOver()) {
    if (startRound()) {
      return true;
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
  return false;
}
