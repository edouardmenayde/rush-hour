#ifndef RUSH_HOUR_CAR_H
#define RUSH_HOUR_CAR_H

enum Direction {
  VERTICAL,
  HORIZONTAL
};

struct Car {
  unsigned int line = 0;
  unsigned int column = 0;
  unsigned int length = 0;
  Direction direction = HORIZONTAL;

  /**
   * Determines if the car is the one we need to the one we need to get out of the Situation.
   */
  bool target = false;
};

#endif //RUSH_HOUR_CAR_H
