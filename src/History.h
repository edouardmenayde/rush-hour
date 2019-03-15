#ifndef RUSH_HOUR_HISTORY_H
#define RUSH_HOUR_HISTORY_H

#include "Situation.h"
#include <vector>

using namespace std;

class HistoryNode {
 public:
  Situation situation;
  vector<HistoryNode *> children;
  HistoryNode *parent = nullptr;

  explicit HistoryNode(const Situation &situation);
  explicit HistoryNode(const Situation &situation, HistoryNode *parent);

  ~HistoryNode();
};

/**
 * Represents the space of situation explored.
 */
class History {
 public:
  HistoryNode *root = nullptr;

  explicit History(const Situation &situation);

  ~History();

  bool exists(const Situation &situation);

  bool exists_aux(const Situation &situation, const HistoryNode *node);
};

#endif //RUSH_HOUR_HISTORY_H
