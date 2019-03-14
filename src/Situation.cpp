#include <fstream>
#include <iostream>
#include "Situation.h"

Situation Situation::from_file(string filename) {
  ifstream file;

  file.open(filename);

  if (file.fail()) {
    cerr << "Could not read file `" << filename << "`." << endl;
  }

  Situation situation;

  string line;

  unsigned int x_exit, y_exit;

  file >> x_exit >> y_exit; // First line consist of the exit coordinates

  situation.exit = Vector2{x_exit, y_exit};

  unsigned int line_pos, column_pos, length;
  bool horizontal;

  bool target = true;

  while (file >> line_pos >> column_pos >> length >> horizontal) {
    situation.cars.push_back(Car{
        line_pos, column_pos, length, horizontal ? HORIZONTAL : VERTICAL, target
    });
    target = false; // After the first pass the following cars are not the target
  }

  file.close();

  situation.compute_parking();

  return situation;
}

void Situation::print() {
  const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (!parking[i][j]) {
        cout << "  ";
      } else {
        cout << alphabet[parking[i][j] - 1] << " ";
      }
    }
    if (i + 1 < SIZE) {
      cout << endl;
    }
  }
}

void Situation::compute_moves() {
  unsigned int car_number = 0;
  for (auto &car : cars) {
    if (car.plane == VERTICAL) {
      if (car.line - 1 >= 0) {
        // We can move UP
        int new_line = car.line - 1;
        if (parking[new_line][car.column] == -1) {
          moves.push_back(Move{car_number, UP});
        }
      }
      if (car.line + car.length < SIZE) {
        // We can move DOWN
        int new_line = car.line + car.length;
        if (parking[new_line][car.column] == -1) {
          moves.push_back(Move{car_number, DOWN});
        }
      }
    } else {
      if (car.column - 1 >= 0) {
        // We can move to the LEFT
        int new_column = car.column - 1;
        if (parking[car.line][new_column] == -1) {
          moves.push_back(Move{car_number, LEFT});
        }
      }
      if (car.column + car.length < SIZE) {
        // We can move to the RIGHT
        int new_column = car.column + car.length;
        if (parking[car.line][new_column] == -1) {
          moves.push_back(Move{car_number, RIGHT});
        }
      }
    }
    car_number++;
  }
}

void Situation::compute_parking() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      parking[i][j] = -1;
    }
  }

  unsigned int car_number = 0;

  for (auto &car : cars) {
    if (car.plane == HORIZONTAL) {
      for (int i = 0; i < car.length; i++) {
        parking[car.line][car.column + i] = car_number;
      }
    } else {
      for (int i = 0; i < car.length; i++) {
        parking[car.line + i][car.column] = car_number;
      }
    }
    car_number++;
  }
}
bool Move::operator==(const Move &rhs) const {
  return car_index == rhs.car_index &&
      direction == rhs.direction;
}
bool Move::operator!=(const Move &rhs) const {
  return !(rhs == *this);
}
ostream &operator<<(ostream &os, const Move &move) {
  os << "(" << move.car_index << ", " << move.direction << ")";
  return os;
}
