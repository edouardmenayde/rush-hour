#include <iostream>
#include "History.h"

History::~History() {
  delete root;
}

History::History(const Situation &situation) {
  root = new HistoryNode(situation);
}

bool History::exists(const Situation &situation) {
  return exists_aux(situation, root);
}

bool History::exists_aux(const Situation &situation, const HistoryNode *node) {
  if (situation == node->situation) {
    return true;
  } else {
    bool found = false;
    int i = 0;
    while (!found && i < node->children.size()) {
      found = exists_aux(situation, node->children[i]);
      i++;
    }
    return found;
  }
}

HistoryNode::HistoryNode(const Situation &s) {
  situation = s;
}

HistoryNode::~HistoryNode() {
  for (auto &child : children) {
    delete child;
  }
}
