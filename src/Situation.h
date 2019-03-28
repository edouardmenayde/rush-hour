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
  uint8_t car_index; // We know we will never have more than 255 cars
  Direction direction;
  uint8_t steps; // We will never have more than 255 steps

  Move(uint8_t i, Direction d, uint8_t s) : car_index(i), direction(d), steps(s) {}

  bool operator==(const Move &rhs) const;
  bool operator!=(const Move &rhs) const;
  friend ostream &operator<<(ostream &os, const Move &move1);
};

const uint8_t SIZE = 6;

typedef array<array<int8_t, SIZE>, SIZE> Parking;
typedef vector<Car> Cars;

/**
 * A parking situation with all the cars in it and the exit.
 */
class Situation {
 public:
  /**
   * Array containing all the cars in the parking including the one we want to move to the exit which is represented by a boolean.
   */
  Cars cars;

  /**
   * Represents the exit of the parking in 2D space.
   */
  Vector2 exit;

  /**
   * 2D array representing the parking with -1 for a free spot, and 0 to n for the car index parked.
   */
  Parking parking;

  explicit Situation(string filename);

  explicit Situation(const Situation &old_situation, const Move &move);

  bool is_solution();

  void print();

  void print(Move &move);

  bool operator==(const Situation &rhs) const;

  bool operator!=(const Situation &rhs) const;

  vector<Move> get_moves();

  void compute_parking();
};

#endif //RUSH_HOUR_SITUATION_H
