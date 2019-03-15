#include <iostream>
#include "Explorer.h"

Explorer::Explorer(Situation &root) {
    History history(root);
    explore(history.root);
}

bool Explorer::explore(HistoryNode *history_node) {
    history_node->situation.compute_moves();
    for (auto &move : history_node->situation.moves) {
        auto new_situation = history_node->situation.move(move);
        if (new_situation.is_solution()) {
            cout<<"Solution found"<<endl;
            return true;
        }
        if (!history.exists(new_situation)) {
            auto new_history_node = new HistoryNode(new_situation);
            history_node->children.push_back(new_history_node);
            explore(new_history_node);
        }
    }
    return false;
}
