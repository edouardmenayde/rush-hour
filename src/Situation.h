#ifndef RUSH_HOUR_SITUATION_H
#define RUSH_HOUR_SITUATION_H

#include <vector>
#include "Vector2.h"
#include "Car.h"
#include <string>

using namespace std;

/**
 * A parking situation with all the cars in it and the exit.
 */
class Situation {
 public:
  /**
   * Array containing all the cars in the parking including the one we want to move to the exit which is represented by a boolean.
   */
  std::vector<Car> cars;

  /**
   * Represents the exit of the parking in 2D space.
   */
  Vector2 exit;

  void print();

  static Situation from_file(string filename);
};

#endif //RUSH_HOUR_SITUATION_H
