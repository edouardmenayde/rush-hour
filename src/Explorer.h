#ifndef RUSH_HOUR_EXPLORER_H
#define RUSH_HOUR_EXPLORER_H

#include "History.h"

class Explorer {
 public:
  explicit Explorer(Situation &root, int max_moves = -1);

  History history;

  void explore(vector<HistoryNode *> history_node);

  void print();

  HistoryNode *solution = nullptr;

  int unique_state_explored = 0;
  int state_explored = 0;
  double time_spent = 0;
  int moves = 0;
  int max_moves = -1;

  bool is_solved();
};

#endif //RUSH_HOUR_EXPLORER_H
