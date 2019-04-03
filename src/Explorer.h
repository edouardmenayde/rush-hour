#ifndef RUSH_HOUR_EXPLORER_H
#define RUSH_HOUR_EXPLORER_H

#include "History.h"

class Explorer {
 private:
  History history;

  const int moves_limit = -1;

  void explore(vector<HistoryNode *> history_node);

 public:
  HistoryNode *solution = nullptr;

  double time_spent = 0;

  int unique_state_explored = 0;

  int state_explored = 0;

  int moves = 0;

  explicit Explorer(Situation &root, int moves_limit = -1);

  const void print();

  const bool is_solved();
};

#endif //RUSH_HOUR_EXPLORER_H
