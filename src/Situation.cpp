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
    Car car = {
        line_pos, column_pos, length, horizontal ? HORIZONTAL : VERTICAL, target
    };
    situation.cars.push_back(car);
    target = false; // After the first pass the following cars are not the target
  }

  file.close();

  return situation;
}

void Situation::print() {
  const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  unsigned int size = 6;

  unsigned int map[size][size];

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      map[i][j] = 0;
    }
  }

  unsigned int car_number = 1;

  for (auto &car : cars) {
    if (car.direction == HORIZONTAL) {
      for (int i = 0; i < car.length; i++) {
        map[car.line][car.column + i] = car_number;
      }
    } else {
      for (int i = 0; i < car.length; i++) {
        map[car.line + i][car.column] = car_number;
      }
    }
    car_number++;
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (!map[i][j]) {
        cout << "  ";
      } else {
        cout << alphabet[map[i][j] - 1] << " ";
      }
    }
    if (i + 1 < size) {
      cout << endl;
    }
  }
}
