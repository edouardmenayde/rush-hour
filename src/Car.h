#ifndef RUSH_HOUR_CAR_H
#define RUSH_HOUR_CAR_H

enum Plane {
  VERTICAL,
  HORIZONTAL
};

const ushort TARGET_CAR_INDEX = 0;

class Car {
 public:
  ushort line = 0;
  ushort column = 0;
  ushort length = 0;
  Plane plane = HORIZONTAL;

  Car(ushort l, ushort c, ushort lgth, Plane p) : line(l), column(c), length(lgth), plane(p) {}

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
