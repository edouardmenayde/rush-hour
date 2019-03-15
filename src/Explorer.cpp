#include <iostream>
#include "Explorer.h"

Explorer::Explorer(Situation &root) : history(History(root)) {
  explore(history.root);
}

bool Explorer::explore(HistoryNode *history_node) {
  history_node->situation.compute_moves();
  for (auto &move : history_node->situation.moves) {
    Situation new_situation;
    history_node->situation.move(move, new_situation);
    if (history.exists(new_situation)) {

    } else if (new_situation.is_solution()) {
      cout << endl << "Solution found" << endl;
      new_situation.print();
      auto new_history_node = new HistoryNode(new_situation);
      history_node->children.push_back(new_history_node);
      return true;
    } else if (!history.exists(new_situation)) {
      auto new_history_node = new HistoryNode(new_situation);
      history_node->children.push_back(new_history_node);
      explore(new_history_node);
    }
  }
  return false;
}
