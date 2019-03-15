#ifndef RUSH_HOUR_EXPLORER_H
#define RUSH_HOUR_EXPLORER_H

#include "History.h"

class Explorer {
 public:
  explicit Explorer(Situation &root);

  History history;

  void explore(vector<HistoryNode *> history_node, int nb_moves);

  HistoryNode *solution;
};

#endif //RUSH_HOUR_EXPLORER_H
