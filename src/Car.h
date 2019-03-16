#ifndef RUSH_HOUR_CAR_H
#define RUSH_HOUR_CAR_H

enum Plane {
  VERTICAL,
  HORIZONTAL
};

const unsigned int TARGET_CAR_INDEX = 0;

class Car {
 public:
  int line = 0;
  int column = 0;
  int length = 0;
  Plane plane = HORIZONTAL;

  Car(int l, int c, int lgth, Plane p) : line(l), column(c), length(lgth), plane(p) {}

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
