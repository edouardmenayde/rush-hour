#include <iostream>
#include "utils.h"
#include "Generator.h"
#include "Situation.h"
#include "Explorer.h"

using namespace std;

bool Range::is_between(int m) {
  return m >= start && m <= end;
}

Generator::Generator(uint8_t difficulty_level) {
#ifndef DEBUG
  std::random_device random;
  generator.seed(random());
#endif
  struct timeval tv1{}, tv2{};

  if (gettimeofday(&tv1, nullptr) != 0) {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }

  Range range;

  bool generating = true;
  int tries = 1;

  while (generating) {
    switch (difficulty_level) {
      case 1: {
        uniform_int_distribution<uint8_t> lvl1_moves_cars(3, 5);
        number_of_cars = lvl1_moves_cars(generator);
        range = Range{1, 10};
        break;
      }
      case 2: {
        uniform_int_distribution<uint8_t> lvl2_moves_cars(5, 7);
        number_of_cars = lvl2_moves_cars(generator);
        range = Range{11, 20};
        break;
      }
      case 3: {
        uniform_int_distribution<uint8_t> lvl3_moves_cars(7, 9);
        number_of_cars = lvl3_moves_cars(generator);
        range = Range{21, 30};
        break;
      }
      case 4: {
        uniform_int_distribution<uint8_t> lvl4_moves_cars(10, 13);
        number_of_cars = lvl4_moves_cars(generator);
        range = Range{31, 40};
        break;
      }
      default:break;
    }

    Situation initial_situation;

    uniform_int_distribution<uint8_t> position_range(0, SIZE - 1);
    uniform_int_distribution<uint8_t> target_line_range(1, SIZE - 2);
    uniform_int_distribution<uint8_t> length_range(2, 3);
    uniform_int_distribution<uint8_t> direction_range(0, 1);

    while (initial_situation.cars.size() < number_of_cars) {
      Car new_car;

      if (initial_situation.cars.empty()) {
        new_car = Car(target_line_range(generator),
                      SIZE - 2,
                      2,
                      Plane::HORIZONTAL);
      } else {
        new_car = Car(position_range(generator),
                      position_range(generator),
                      length_range(generator),
                      direction_range
                          (generator) ? Plane::HORIZONTAL
                                      : Plane::VERTICAL);
      }

      bool valid = true;
      if (new_car.plane == Plane::VERTICAL) {
        int8_t i = new_car.line;

        while (valid && i < new_car.length + new_car.line) {
          if (i < 0 || i >= SIZE) {
            valid = false;
          } else if (initial_situation.parking.at((unsigned long) i).at(new_car.column) != EMPTY) {
            valid = false;
          }

          ++i;
        }
      } else {
        int8_t i = new_car.column;

        while (valid && i < new_car.length + new_car.column) {
          if (i < 0 || i >= SIZE) {
            valid = false;
          } else if (initial_situation.parking.at(new_car.line).at((unsigned long) i) != EMPTY) {
            valid = false;
          }

          ++i;
        }
      }

      if (valid) {
        if (initial_situation.cars.empty()) {
          initial_situation.exit = Vector2{new_car.line, 0};
        }
        initial_situation.cars.push_back(new_car);
        initial_situation.compute_parking();
      }
    }

    cout << "Try " << tries << endl;
    Explorer explorer(initial_situation, range.end);
    ++tries;

    if (explorer.is_solved() && range.is_between(explorer.moves)) {
      generating = false;
      cout << "Generated a solvable puzzle after " << tries << " tries with " <<  explorer.moves <<  " moves : " <<
      endl;
      explorer.print();
    }
  }

  if (gettimeofday(&tv2, nullptr) != 0) {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }

  double time_spent = timevalsub(&tv1, &tv2);

  cout << "Generated puzzle in " << time_spent << endl;

}
