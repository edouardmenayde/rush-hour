#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Situation.h"

// Move

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

// Situation

Situation::Situation(string filename) {
  ifstream file;

  file.open(filename);

  if (file.fail()) {
    cerr << "Could not read file `" << filename << "`." << endl;
  }

  string line;

  unsigned int x_exit, y_exit;

  file >> x_exit >> y_exit; // First line consist of the exit coordinates

  exit = Vector2{x_exit, y_exit};

  int line_pos, column_pos, length;
  bool horizontal;

  while (file >> line_pos >> column_pos >> length >> horizontal) {
    cars.push_back(Car{
        line_pos, column_pos, length, horizontal ? HORIZONTAL : VERTICAL
    });
  }

  file.close();

  compute_parking();
}

void Situation::print() {
  const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (parking[i][j] == -1) {
        cout << "  ";
      } else {
        cout << alphabet[parking[i][j]] << " ";
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

void Situation::move(Move move, Situation &new_situation) {
  copy(cars.begin(), cars.end(), back_inserter(new_situation.cars));

  auto &car = new_situation.cars[move.car_index];

  switch (move.direction) {
    case UP:car.line -= 1;
      break;
    case DOWN:car.line += 1;
      break;
    case RIGHT:car.column += 1;
      break;
    case LEFT:car.column -= 1;
      break;
  }

  new_situation.exit = exit;

  new_situation.compute_parking();
}

bool Situation::is_solution() {
  return parking[exit.line][exit.column] == TARGET_CAR_INDEX;
}

bool Situation::operator==(const Situation &rhs) const {
  return std::equal(cars.begin(), cars.end(), rhs.cars.begin());
}

bool Situation::operator!=(const Situation &rhs) const {
  return !(rhs == *this);
}
Situation &Situation::operator=(const Situation &old_situation) {
  copy(old_situation.cars.begin(), old_situation.cars.end(), back_inserter(this->cars));
  exit = old_situation.exit;
  compute_parking();

  return *this;
}
