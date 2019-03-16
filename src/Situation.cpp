#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Situation.h"
#include "deps/termcolor.hpp"

// Move

bool Move::operator==(const Move &rhs) const {
  return car_index == rhs.car_index &&
      direction == rhs.direction;
}
bool Move::operator!=(const Move &rhs) const {
  return !(rhs == *this);
}
ostream &operator<<(ostream &os, const Move &move) {
  os << "(" << move.car_index << ", " << move.direction << ", " << move.steps << ")";
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
  const string alphabet = "=BCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (parking[i][j] == -1) {
        cout << "  ";
      } else if (parking[i][j] == 0) {
        cout << termcolor::yellow << termcolor::bold << alphabet[parking[i][j]] << termcolor::reset << " ";
      } else {
        cout << alphabet[parking[i][j]] << " ";
      }
    }
    if (i + 1 < SIZE) {
      cout << endl;
    }
  }
}

void Situation::print(Move &move) {
  const string alphabet = "=BCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (parking[i][j] == -1) {
        cout << "  ";
      } else if (parking[i][j] == 0) {
        cout << termcolor::blue << termcolor::bold << alphabet[parking[i][j]] << termcolor::reset << " ";
      }
      else if (parking[i][j] == move.car_index) {
        cout << termcolor::yellow << termcolor::bold << alphabet[parking[i][j]] << termcolor::reset << " ";
      }
      else {
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
      for (int i = 1; i < SIZE; i++) {
        if (car.line - i >= 0) {
          // We can move UP
          bool valid_move = true;
          for (int j = 1; j <= i; j++) {
            if (parking[car.line - j][car.column] != -1) {
              valid_move = false;
            }
          }

          if (valid_move) {
            moves.push_back(Move{car_number, UP, i});
          }
        }
        if (car.line + car.length + (i - 1) < SIZE) {
          // We can move DOWN
          bool valid_move = true;
          for (int j = 1; j <= i; j++) {
            if (parking[car.line + car.length + (j - 1)][car.column] != -1) {
              valid_move = false;
            }
          }

          if (valid_move) {
            moves.push_back(Move{car_number, DOWN, i});
          }
        }
      }
    } else {
      for (int i = 1; i < SIZE; i++) {
        if (car.column - i >= 0) {
          // We can move to the LEFT
          bool valid_move = true;
          for (int j = 1; j <= i; j++) {
            if (parking[car.line][car.column - j] != -1) {
              valid_move = false;
            }
          }

          if (valid_move) {
            moves.push_back(Move{car_number, LEFT, i});
          }
        }
        if (car.column + car.length + (i - 1) < SIZE) {
          // We can move to the RIGHT
          bool valid_move = true;
          for (int j = 1; j <= i; j++) {
            if (parking[car.line][car.column + car.length + (j - 1)] != -1) {
              valid_move = false;
            }
          }

          if (valid_move) {
            moves.push_back(Move{car_number, RIGHT, i});
          }
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
    case UP:car.line -= move.steps;
      break;
    case DOWN:car.line += move.steps;
      break;
    case RIGHT:car.column += move.steps;
      break;
    case LEFT:car.column -= move.steps;
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

