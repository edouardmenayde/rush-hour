#include <iostream>
#include "deps/termcolor.hpp"
#include "Explorer.h"
#include "utils.h"

Explorer::Explorer(Situation &root, int m) : history(History(root)), max_moves(m) {
  vector<HistoryNode *> nodes;
  nodes.push_back(history.root);

  struct timeval tv1{}, tv2{};

  if (gettimeofday(&tv1, nullptr) != 0) {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }

  explore(nodes);

  if (gettimeofday(&tv2, nullptr) != 0) {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }

  time_spent = timevalsub(&tv1, &tv2);
}

void Explorer::print() {
  vector<HistoryNode *> history(0);

  HistoryNode *current_node = solution;

  while (current_node != nullptr) {
    history.push_back(current_node);
    current_node = current_node->parent;
  }

  cout << "Found a solution :" << endl
       << "- in " << termcolor::red << time_spent << "s" << termcolor::reset << endl
       << "- exploring " << termcolor::red << state_explored << termcolor::reset << " states (" << unique_state_explored
       << " uniques)" << endl
       << "- in " << termcolor::red << static_cast<int>(history.size() - 1) << termcolor::reset << " moves" << endl
       << endl;

  for (int j = static_cast<int>(history.size() - 1); j >= 0; j--) {
    if (auto m = history[j]->move) {
      history[j]->situation.print(*m);
    }
    else {
      history[j]->situation.print();
    }
    cout << endl;
    cout << endl;
  }
}

void Explorer::explore(vector<HistoryNode *> nodes) {
  bool exploring = true;

  while (exploring) {
    if (max_moves != -1 && moves > max_moves) {
      return;
    }

    moves++;
    vector<HistoryNode *> new_nodes;
    for (auto &node : nodes) {
      auto moves = node->situation.get_moves();
      for (auto &move : moves) {
        Situation new_situation(node->situation, move);
        state_explored++;

        if (!history.exists(new_situation, node)) {
          auto new_history_node = new HistoryNode(new_situation, move, node);
          node->children.push_back(new_history_node);
          unique_state_explored++;

          if (new_situation.is_solution()) {
            solution = new_history_node;
            return;
          } else {
            new_nodes.push_back(new_history_node);
          }
        }
      }
    }

    nodes.erase(nodes.begin(), nodes.end());
    copy(new_nodes.begin(), new_nodes.end(), back_inserter(nodes));

    exploring = !new_nodes.empty();
  }
}
bool Explorer::is_solved() {
  return solution != nullptr;
}
