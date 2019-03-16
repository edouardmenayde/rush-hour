#include <iostream>
#include "History.h"

History::~History() {
  delete root;
}

History::History(const Situation &situation) {
  root = new HistoryNode(situation);
}

bool History::exists(const Situation &situation, const HistoryNode *skippable) {
  return exists_aux(situation, root, skippable);
}

bool History::exists_aux(const Situation &situation, const HistoryNode *node, const HistoryNode *skippable) {
  if (node == skippable) {
    // If we can skip the node we can skip all the direct children
    int i = 0;
    bool found = false;
    while (!found && i < node->children.size()) {
      int j = 0;
      while (!found && j < node->children[i]->children.size()) {
        found = exists_aux(situation, node->children[i]->children[j], skippable);
        j++;
      }
      i++;
    }
  } else {
    if (situation == node->situation) {
      return true;
    } else {
      bool found = false;
      int i = 0;
      while (!found && i < node->children.size()) {
        found = exists_aux(situation, node->children[i], skippable);
        i++;
      }
      return found;
    }
  }
}

HistoryNode::HistoryNode(const Situation &s) {
  situation = s;
}

HistoryNode::HistoryNode(const Situation &s, Move m, HistoryNode *p) {
  situation = s;
  parent = p;
  move = m;
}

HistoryNode::~HistoryNode() {
  for (auto &child : children) {
    delete child;
  }
}
