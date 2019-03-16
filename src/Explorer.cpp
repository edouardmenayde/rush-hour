#include <iostream>
#include "Explorer.h"
#include <sys/time.h>
#include "deps/termcolor.hpp"

double timevalsub(struct timeval *tv1, const struct timeval *tv2) {
  double res = 0;
  res = tv2->tv_sec - tv1->tv_sec;
  res += (tv2->tv_usec - tv1->tv_usec) * 1.0 / 1000000;
  return res;
}

Explorer::Explorer(Situation &root) : history(History(root)) {
  vector<HistoryNode *> nodes;
  nodes.push_back(history.root);

  struct timeval tv1{}, tv2{};
  int err;

  err = gettimeofday(&tv1, nullptr);
  if (err != 0) {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }

  explore(nodes);

  err = gettimeofday(&tv2, nullptr);
  if (err != 0) {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }

  double amount_of_time = timevalsub(&tv1, &tv2);

  vector<HistoryNode *> history(0);

  HistoryNode *current_node = solution;

  while (current_node != nullptr) {
    history.push_back(current_node);
    current_node = current_node->parent;
  }

  cout << "Found a solution :" << endl
       << "- in " << termcolor::red << amount_of_time << "s" << termcolor::reset << endl
       << "- exploring " << termcolor::red << state_explored << termcolor::reset << " states (" << unique_state_explored
       << " uniques)" << endl
       << "- in " << termcolor::red << static_cast<int>(history.size() - 1) << termcolor::reset << " moves" << endl << endl;

  for (int j = static_cast<int>(history.size() - 1); j >= 0; j--) {
    history[j]->situation.print(history[j]->move);
    cout << endl;
    cout << endl;
  }
}

void Explorer::explore(vector<HistoryNode *> nodes) {
  vector<HistoryNode *> new_nodes;

  for (auto &node : nodes) {
    node->situation.compute_moves();
    for (auto &move : node->situation.moves) {
      Situation new_situation;
      node->situation.move(move, new_situation);
      state_explored++;

      if (!history.exists(new_situation)) {
        auto new_history_node = new HistoryNode(new_situation, move, node);
        node->children.push_back(new_history_node);
        unique_state_explored++;
        new_nodes.push_back(new_history_node);

        if (new_situation.is_solution()) {
          solution = new_history_node;
          return;
        }
      }
    }
  }

  if (!new_nodes.empty()) {
    explore(new_nodes);
  }
}
