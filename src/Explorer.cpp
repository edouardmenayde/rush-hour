#include <iostream>
#include "deps/termcolor.hpp"
#include "Explorer.h"
#include "utils.h"

Explorer::Explorer(const Situation &root, int m) : moves_limit(m), initial_situation(root) {
  history.emplace(initial_situation.parking);
  deque<pair<Situation, Moves>> situations;
  situations.emplace_back(initial_situation, list<Move>());

  struct timeval tv1{}, tv2{};

  if (gettimeofday(&tv1, nullptr) != 0) {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }

  explore(situations);

  if (gettimeofday(&tv2, nullptr) != 0) {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }

  time_spent = timevalsub(&tv1, &tv2);
}

void Explorer::print() const {
  if (auto moves = solution) {
    auto situation = initial_situation;
    situation.print();
    for (const auto &m : *moves) {
      cout << endl << endl;
      Situation new_situation = Situation(situation, m);
      new_situation.print(m);
      situation = new_situation;
    }
    cout << endl << endl << "Found a solution :" << endl;
    cout << "- in " << termcolor::red << time_spent << "s" << termcolor::reset << endl
         << "- exploring " << termcolor::red << state_explored << termcolor::reset << " states ("
         << unique_state_explored
         << " uniques)" << endl
         << "- in " << termcolor::red << ((*moves).size()) << termcolor::reset << " moves"
         << endl
         << endl;
  } else {
    cout << "Found no solution :" << endl;
    cout << "- in " << termcolor::red << time_spent << "s" << termcolor::reset << endl
         << "- exploring " << termcolor::red << state_explored << termcolor::reset << " states ("
         << unique_state_explored
         << " uniques)" << endl
         << endl
         << endl;
  }
}

void Explorer::explore(deque<pair<Situation, Moves>> &situations) {
  bool exploring = true;

  while (exploring) {
    if (moves_limit != -1 && move_number > moves_limit) {
      cout << "Stopping after " << move_number << " moves (limit is " << moves_limit << ")." << endl;
      return;
    }

    move_number++;
    deque<pair<Situation, Moves>> new_situations;
    for (auto &situation : situations) {
      for (const auto &move : situation.first.get_moves()) {
        Situation new_situation(situation.first, move);
        state_explored++;

        if (history.find(new_situation.parking) == history.end()) {
          list<Move> m(situation.second);
          m.push_back(move);
          unique_state_explored++;

          if (new_situation.is_solution()) {
            solution = m;
            return;
          } else {
            history.insert(new_situation.parking);
            new_situations.emplace_back(new_situation, m);
          }
        }
      }
    }

    situations.erase(situations.begin(), situations.end());
    copy(new_situations.begin(), new_situations.end(), back_inserter(situations));

    exploring = !new_situations.empty();
  }
}
bool Explorer::is_solved() const {
  return solution.has_value();
}
