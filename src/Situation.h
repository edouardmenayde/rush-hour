#ifndef RUSH_HOUR_SITUATION_H
#define RUSH_HOUR_SITUATION_H

#include <vector>
#include <array>
#include "Vector2.h"
#include "Car.h"
#include <string>
#include <ostream>
#include "Direction.h"

using namespace std;

class Move {
 public:
  unsigned int car_index;
  Direction direction;
  bool operator==(const Move &rhs) const;
  bool operator!=(const Move &rhs) const;
  friend ostream &operator<<(ostream &os, const Move &move1);
};

const unsigned int SIZE = 6;

/**
 * A parking situation with all the cars in it and the exit.
 */
class Situation {
 public:
  void compute_parking();
  array<array<int, SIZE>, SIZE> parking{};

  vector<Move> moves{};
  /**
   * Array containing all the cars in the parking including the one we want to move to the exit which is represented by a boolean.
   */
  std::vector<Car> cars{};

  /**
   * Represents the exit of the parking in 2D space.
   */
  Vector2 exit{};

  Situation() = default;
  explicit Situation(string filename);

  bool is_solution();

  void print();

  void compute_moves();

  bool operator==(const Situation &rhs) const;

  bool operator!=(const Situation &rhs) const;

  Situation &operator=(const Situation &old_situation);

  void move(Move move, Situation &new_situation);
};

#endif //RUSH_HOUR_SITUATION_H
