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
  os << "(" << (int) move.car_index << ", " << (int) move.direction << ", " << (int) move.steps << ")";
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

  ushort x_exit, y_exit;

  file >> x_exit >> y_exit; // First line consist of the exit coordinates

  exit = Vector2{(uint8_t) x_exit, (uint8_t) y_exit};

  ushort line_pos, column_pos, length;
  bool horizontal;

  while (file >> line_pos >> column_pos >> length >> horizontal) {
    cars.emplace_back(
        line_pos, column_pos, length, horizontal ? Plane::HORIZONTAL : Plane::VERTICAL
    );
  }

  file.close();

  compute_parking();
}

void Situation::print() {
  for (int8_t i = 0; i < SIZE; i++) {
    for (int8_t j = 0; j < SIZE; j++) {
      if (parking.at((unsigned long) i).at((unsigned long) j) == -1) {
        cout << "  ";
      } else if (parking.at((unsigned long) i).at((unsigned long) j) == 0) {
        cout << termcolor::blue << termcolor::bold << ALPHABET[parking.at((unsigned long) i).at((unsigned long) j)] <<
             termcolor::reset
             << " ";
      } else {
        cout << ALPHABET[parking.at((unsigned long) i).at((unsigned long) j)] << " ";
      }
    }
    if (i + 1 < SIZE) {
      cout << endl;
    }
  }
}

void Situation::print(Move &move) {
  for (int8_t i = 0; i < SIZE; i++) {
    for (int8_t j = 0; j < SIZE; j++) {
      if (parking.at((unsigned long) i).at((unsigned long) j) == -1) {
        cout << "  ";
      } else if (parking.at((unsigned long) i).at((unsigned long) j) == 0) {
        cout << termcolor::blue << termcolor::bold << ALPHABET[parking.at((unsigned long) i).at((unsigned long) j)]
             << termcolor::reset << " ";
      } else if (parking.at((unsigned long) i).at((unsigned long) j) == move.car_index) {
        cout << termcolor::yellow << termcolor::bold << ALPHABET[parking.at((unsigned long) i).at((unsigned long) j)]
             << termcolor::reset << " ";
      } else {
        cout << ALPHABET[parking.at((unsigned long) i).at((unsigned long) j)] << " ";
      }
    }
    if (i + 1 < SIZE) {
      cout << endl;
    }
  }
}

vector<Move> Situation::get_moves() {
  vector<Move> moves;
  uint8_t car_number = 0;
  const uint8_t MAX_MOVES = 4;
  for (auto &car : cars) {
    if (car.plane == Plane::VERTICAL) {
      {
        uint8_t i = 1;

        while (i <= MAX_MOVES && car.line - i >= 0 && parking.at(car.line - i).at(car.column) == EMPTY) {
          moves.emplace_back(car_number, Direction::UP, i);
          i++;
        }
      }

      {
        uint8_t i = 1;

        while (i <= MAX_MOVES && car.line + car.length - 1 + i < SIZE
            && parking.at((unsigned long) car.line + car.length - 1 + i).at(car.column) == EMPTY) {
          moves.emplace_back(car_number, Direction::DOWN, i);
          i++;
        }
      }
    } else {
      {
        uint8_t i = 1;
        while (i <= MAX_MOVES && car.column - i >= 0 && parking.at(car.line).at(car.column - i) == EMPTY) {
          moves.emplace_back(car_number, Direction::LEFT, i);
          i++;
        }
      }

      {
        uint8_t i = 1;
        while (i <= MAX_MOVES && car.column + car.length - 1 + i < SIZE
            && parking.at(car.line).at((unsigned long) car.column + car.length - 1 + i) == EMPTY) {
          moves.emplace_back(car_number, Direction::RIGHT, i);
          i++;
        }
      }
    }
    car_number++;
  }

  return moves;
}

void Situation::compute_parking() {
  reset_parking();
  int8_t i = 0;
  for (const auto &car : cars) {
    if (car.plane == Plane::HORIZONTAL) {
      for (int j = 0; j < car.length; j++) {
        parking.at(car.line).at((unsigned long) car.column + j) = (int8_t) i;
      }
    } else {
      for (int j = 0; j < car.length; j++) {
        parking.at((unsigned long) car.line + j).at(car.column) = (int8_t) i;
      }
    }
    i++;
  }
}

Situation::Situation(
    const Situation &old_situation,
    const Move &move) {
  copy(old_situation.cars.begin(), old_situation.cars.end(), back_inserter(cars));

  auto &car = cars.at(move.car_index);

  switch (move.direction) {
    case Direction::UP:car.line -= move.steps;
      break;
    case Direction::DOWN:car.line += move.steps;
      break;
    case Direction::RIGHT:car.column += move.steps;
      break;
    case Direction::LEFT:car.column -= move.steps;
      break;
    default:perror("Unrecognized move");
  }

  exit = old_situation.exit;

  compute_parking();
}

bool Situation::is_solution() {
  return parking.at(exit.line).at(exit.column) == TARGET_CAR_INDEX;
}

bool Situation::operator==(const Situation &rhs) const {
  return std::equal(cars.begin(), cars.end(), rhs.cars.begin());
}

bool Situation::operator!=(const Situation &rhs) const {
  return !(rhs == *this);
}
Situation::Situation() {
  reset_parking();
}
void Situation::reset_parking() {
  for (int8_t i = 0; i < SIZE; i++) {
    for (int8_t j = 0; j < SIZE; j++) {
      parking.at((unsigned long) i).at((unsigned long) j) = -1;
    }
  }
}
