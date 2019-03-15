#include <iostream>
#include "Explorer.h"
#include <sys/time.h>

double timevalsub(struct timeval *tv1, const struct timeval *tv2) {
  double res = 0;
  res = tv2->tv_sec - tv1->tv_sec;
  res += (tv2->tv_usec - tv1->tv_usec) * 1.0 / 1000000;
  return res;
}

Explorer::Explorer(Situation &root) : history(History(root)) {
  int nb_moves = 0;
  vector<HistoryNode *> nodes;
  nodes.push_back(history.root);

  struct timeval tv1, tv2;
  int err;

  err = gettimeofday(&tv1, NULL);
  if (err != 0) {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }

  explore(nodes, nb_moves);

  err = gettimeofday(&tv2, NULL);
  if (err != 0) {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }
  double amount_of_time = timevalsub(&tv1, &tv2);

  vector<HistoryNode *> history;

  HistoryNode *current_node = solution;

  while (current_node != nullptr) {
    history.push_back(current_node);
    current_node = current_node->parent;
  }

  cout << "Found a solution :" << endl
       << "- in " << amount_of_time << "s" << endl
       << "- exploring " << state_explored << " states " << endl
       << "- in " << history.size() - 1 << " moves" << endl << endl;

  for (int j = static_cast<int>(history.size() - 1); j >= 0; j--) {
    history[j]->situation.print();
    cout << endl;
    cout << endl;
  }
}

void Explorer::explore(vector<HistoryNode *> nodes, int nb_moves) {
  vector<HistoryNode *> new_nodes;

  for (auto &node : nodes) {
    node->situation.compute_moves();
    for (auto &move : node->situation.moves) {
      Situation new_situation;
      node->situation.move(move, new_situation);
      state_explored++;

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
