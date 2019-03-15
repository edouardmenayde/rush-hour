#ifndef RUSH_HOUR_HISTORY_H
#define RUSH_HOUR_HISTORY_H

#include "Situation.h"
#include <vector>

using namespace std;

class HistoryNode {
public:
    Situation situation;
    vector<HistoryNode *> children;

    explicit HistoryNode(const Situation &situation);

    ~HistoryNode();
};

/**
 * Represents the space of situation explored.
 */
class History {
public:
    HistoryNode *root = nullptr;

    History() = default;

    explicit History(const Situation &situation);

    ~History();

    bool exists(const Situation &situation);

    bool exists_aux(const Situation &situation,const HistoryNode *node);
};

#endif //RUSH_HOUR_HISTORY_H
