#include <iostream>
#include "Explorer.h"

Explorer::Explorer(Situation &root) : history(History(root)) {
  int nb_moves = 0;
  vector<HistoryNode *> nodes;
  nodes.push_back(history.root);
  explore(nodes, nb_moves);

  vector<HistoryNode *> history;

  HistoryNode *current_node = solution;

  while (current_node != nullptr) {
    history.push_back(current_node);
    current_node = current_node->parent;
  }

  cout << "Solutions en " << history.size() - 1 << " coups: " << endl;

  for (int j = static_cast<int>(history.size() - 1); j >= 0; j--) {
    history[j]->situation.print();
    cout << endl;
    cout << endl;
  }

  cout << endl;
}

void Explorer::explore(vector<HistoryNode *> nodes, int nb_moves) {
  vector<HistoryNode *> new_nodes;

  cout << "Exploring at layer : " << nb_moves << endl;

  for (auto &node : nodes) {
    node->situation.compute_moves();
    for (auto &move : node->situation.moves) {
      Situation new_situation;
      node->situation.move(move, new_situation);

      if (new_situation.is_solution()) {
        auto new_history_node = new HistoryNode(new_situation, node);
        node->children.push_back(new_history_node);
        solution = new_history_node;
        return;
      } else if (!history.exists(new_situation)) {
        auto new_history_node = new HistoryNode(new_situation, node);
        node->children.push_back(new_history_node);

        new_nodes.push_back(new_history_node);
      }
    }
  }

  if (!new_nodes.empty()) {
    explore(new_nodes, nb_moves + 1);
  }
}
