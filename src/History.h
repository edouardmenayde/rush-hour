#ifndef RUSH_HOUR_HISTORY_H
#define RUSH_HOUR_HISTORY_H

#include "Situation.h"
#include <vector>

using namespace std;

class HistoryNode {
 public:
  Situation situation;
  Move move;
  vector<HistoryNode *> children;
  HistoryNode *parent = nullptr;

  explicit HistoryNode(const Situation &situation);
  explicit HistoryNode(const Situation &situation, Move move, HistoryNode *parent);

  ~HistoryNode();
};

/**
 * Represents the space of situation explored.
 */
class History {
 private:
  bool exists_aux(const Situation &situation, const HistoryNode *node, const HistoryNode *skippable);

 public:
  HistoryNode *root = nullptr;

  explicit History(const Situation &situation);

  ~History();
  bool exists(const Situation &situation, const HistoryNode *skippable);
};

#endif //RUSH_HOUR_HISTORY_H
