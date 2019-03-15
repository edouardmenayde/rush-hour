#include <iostream>
#include "Explorer.h"

Explorer::Explorer(Situation &root) : history(History(root)) {
  int nb_moves = 0;
  vector<HistoryNode *> nodes;
  nodes.push_back(history.root);
  explore(nodes, nb_moves);

  vector<vector<HistoryNode *>> histories;
  int current_solution_index = 0;
  int min_index = 0;
  int min = 0;

  for (auto &sol : solutions) {
    vector<HistoryNode *> history;

    HistoryNode *current_node = sol;

    while (current_node != nullptr) {
      history.push_back(current_node);
      current_node = current_node->parent;
    }

    if (current_solution_index == 0) {
      min = static_cast<int>(history.size());
    } else if (history.size() < min) {
      min = static_cast<int>(history.size());
      min_index = current_solution_index;
    }

    current_solution_index++;
    histories.push_back(history);
  }

  vector<HistoryNode*> best_solution = histories[min_index];

  cout << "Solutions en " << min << " coups: " << endl;

  for (int j = static_cast<int>(best_solution.size() - 1); j >= 0; j--) {
    best_solution[j]->situation.print();
    cout << endl;
    cout << endl;
  }

  cout << endl;
}

void Explorer::explore(vector<HistoryNode *> nodes, int nb_moves) {
  vector<HistoryNode *> new_nodes;

  for (auto &node : nodes) {
    node->situation.compute_moves();
    for (auto &move : node->situation.moves) {
      Situation new_situation;
      node->situation.move(move, new_situation);

      if (new_situation.is_solution()) {
        auto new_history_node = new HistoryNode(new_situation, node);
        node->children.push_back(new_history_node);
        solutions.push_back(new_history_node);
      } else if (!history.exists(new_situation)) {
        auto new_history_node = new HistoryNode(new_situation, node);
        node->children.push_back(new_history_node);

        new_nodes.push_back(new_history_node);

        // Update if number of moves less than stack
      }
    }
  }

  if (!new_nodes.empty()) {
    explore(new_nodes, nb_moves + 1);
  }
}
