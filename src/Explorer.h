#ifndef RUSH_HOUR_EXPLORER_H
#define RUSH_HOUR_EXPLORER_H

#include "History.h"

class Explorer {
public:
    explicit Explorer(Situation &root);

    History history;

    bool explore(HistoryNode *history_node);
};

#endif //RUSH_HOUR_EXPLORER_H
