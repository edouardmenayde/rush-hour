#ifndef RUSH_HOUR_EXPLORER_H
#define RUSH_HOUR_EXPLORER_H

#include <vector>
#include <unordered_set>
#include <list>
#include "Situation.h"

typedef list<Move> Moves;

class Explorer {
 private:
  const int moves_limit = -1;

  void explore(vector<pair<Situation, Moves>> &situations);

  unordered_set<Parking, parking_hash> history;
 public:
  Situation initial_situation;

  optional<Moves> solution;

  double time_spent = 0;

  int unique_state_explored = 0;

  int state_explored = 0;

  int move_number = 0;

  explicit Explorer(const Situation &root, int moves_limit = -1);

  void print() const;

  bool is_solved() const;
};

#endif //RUSH_HOUR_EXPLORER_H
