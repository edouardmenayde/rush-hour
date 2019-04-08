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
  Direction direction;
  uint8_t car_index; // We know we will never have more than 255 cars
  uint8_t steps; // We will never have more than 255 steps

  Move(uint8_t i, Direction d, uint8_t s) : direction(d), car_index(i), steps(s) {}

  bool operator==(const Move &rhs) const;
  bool operator!=(const Move &rhs) const;
  friend ostream &operator<<(ostream &os, const Move &move1);
};

const uint8_t SIZE = 6;

const int8_t EMPTY = -1;

typedef array<array<int8_t, SIZE>, SIZE> Parking;

struct parking_hash {
  template<class Parking>
  size_t operator()(const Parking &parking) const {
    string parking_key;

    for (const auto &lane : parking) {
      for (const auto &spot : lane) {
        parking_key.push_back(spot);
      }
    }

    return hash<string>()(parking_key);
  }
};

typedef vector<Car> Cars;

const string ALPHABET = "=ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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

  explicit Situation();

  explicit Situation(const string filename);

  explicit Situation(const Situation &old_situation, const Move &move);

  void save(const string filename);

  bool is_solution() const;

  void print() const;

  void print(const Move &move) const;

  bool operator==(const Situation &rhs) const;

  bool operator!=(const Situation &rhs) const;

  vector<Move> get_moves() const;

  void compute_parking();

  void reset_parking();
};

#endif //RUSH_HOUR_SITUATION_H
