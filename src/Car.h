#ifndef RUSH_HOUR_CAR_H
#define RUSH_HOUR_CAR_H

#include <ostream>

enum Plane {
  VERTICAL,
  HORIZONTAL
};

const uint8_t TARGET_CAR_INDEX = 0;

class Car {
 public:
  uint8_t line = 0;
  uint8_t column = 0;
  uint8_t length = 0;
  Plane plane = HORIZONTAL;

  Car(uint8_t l, uint8_t c, uint8_t lgth, Plane p) : line(l), column(c), length(lgth), plane(p) {}

  bool operator==(const Car &rhs) const {
    return line == rhs.line &&
        column == rhs.column &&
        length == rhs.length &&
        plane == rhs.plane;
  }
  bool operator!=(const Car &rhs) const {
    return !(rhs == *this);
  }
  friend std::ostream &operator<<(std::ostream &os, const Car &car) {
    os << "(" << (int) car.line << ", " << (int) car.column << ", " << (int) car.length << ", " << car.plane << ")";
    return os;
  }
};

#endif //RUSH_HOUR_CAR_H
