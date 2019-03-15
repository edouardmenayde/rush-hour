#ifndef RUSH_HOUR_CAR_H
#define RUSH_HOUR_CAR_H

enum Plane {
  VERTICAL,
  HORIZONTAL
};

const unsigned int TARGET_CAR_INDEX = 0;

struct Car {
  unsigned int line = 0;
  unsigned int column = 0;
  unsigned int length = 0;
  Plane plane = HORIZONTAL;
};

#endif //RUSH_HOUR_CAR_H
