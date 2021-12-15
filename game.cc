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

void Game::startRound() {
  // suffle deck and deal cards
  deck.shuffle();
  for (int i{0}; i < 4; ++i) {
    players[i].get()->dealHand(deck.dealCard(i));
  }
  // determine who has 7S
  int SSPlayer = deck.whoHas7S();
  // start Round

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
}

void Game::startGame() {
  while(!gameOver()) {
    startRound();
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
