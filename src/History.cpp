#include "History.h"

History::~History() {
  delete root;
}
History::History(const Situation &situation) {
  root = new HistoryNode(situation);
}

HistoryNode::HistoryNode(const Situation &s) {
  situation = s;
}

HistoryNode::~HistoryNode() {
  for (auto &child : childrens) {
    delete child;
  }
}
