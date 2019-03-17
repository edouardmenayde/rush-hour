#ifndef RUSH_HOUR_EXPLORER_H
#define RUSH_HOUR_EXPLORER_H

#include "History.h"

class Explorer {
 public:
  explicit Explorer(Situation &root);

  History history;

  void explore(vector<HistoryNode *> history_node);

  HistoryNode *solution = nullptr;

  int unique_state_explored = 0;
  int state_explored = 0;
};

#endif //RUSH_HOUR_EXPLORER_H
