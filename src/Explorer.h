#ifndef RUSH_HOUR_EXPLORER_H
#define RUSH_HOUR_EXPLORER_H

#include "History.h"

class Explorer {
 public:
  explicit Explorer(const Situation &root);
  History history;
  bool explore();
};

#endif //RUSH_HOUR_EXPLORER_H
