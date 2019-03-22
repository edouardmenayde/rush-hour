#ifndef RUSH_HOUR_CAR_H
#define RUSH_HOUR_CAR_H

enum Plane {
  VERTICAL,
  HORIZONTAL
};

const unsigned int TARGET_CAR_INDEX = 0;

class Car {
 public:
  unsigned char line = 0;
  unsigned char column = 0;
  unsigned char length = 0;
  Plane plane = HORIZONTAL;

  Car(unsigned char l, unsigned char c, unsigned char lgth, Plane p) : line(l), column(c), length(lgth), plane(p) {}

  bool operator==(const Car &rhs) const {
    return line == rhs.line &&
        column == rhs.column &&
        length == rhs.length &&
        plane == rhs.plane;
  }
  bool operator!=(const Car &rhs) const {
    return !(rhs == *this);
  }
};

#endif //RUSH_HOUR_CAR_H
