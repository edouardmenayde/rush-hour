#include <iostream>
#include <fstream>
#include "utils.h"
#include "Generator.h"
#include "Situation.h"
#include "Explorer.h"

bool Range::is_between(int m) {
  return m >= start && m <= end;
}

uniform_int_distribution<uint8_t> position_range(0, SIZE - 1);
uniform_int_distribution<uint8_t> target_line_range(1, SIZE - 2);
uniform_int_distribution<uint8_t> length_range(2, 3);
uniform_int_distribution<uint8_t> direction_range(0, 1);

Generator::Generator(uint8_t d) : difficulty_level(d) {
  random_device random;
  random_generator.seed(random());

  struct timeval tv1{}, tv2{};

  if (gettimeofday(&tv1, nullptr) != 0) {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }

  switch (difficulty_level) {
    case 1: {
      uniform_int_distribution<uint8_t> lvl1_moves_cars(3, 5);
      number_of_cars = lvl1_moves_cars(random_generator);
      range = Range{1, 10};
      break;
    }
    case 2: {
      uniform_int_distribution<uint8_t> lvl2_moves_cars(5, 7);
      number_of_cars = lvl2_moves_cars(random_generator);
      range = Range{10, 20};
      break;
    }
    case 3: {
      uniform_int_distribution<uint8_t> lvl3_moves_cars(11, 13);
      number_of_cars = lvl3_moves_cars(random_generator);
      range = Range{20, 30};
      break;
    }
    case 4: {
      uniform_int_distribution<uint8_t> lvl4_moves_cars(11, 13);
      number_of_cars = lvl4_moves_cars(random_generator);
      range = Range{30, 40};
      break;
    }
    default:break;
  }

  cout << "Generating puzzle with " << (int) number_of_cars << " cars and between " << range.start << " and " << range
      .end << " moves." << endl;

  int number_of_threads = std::thread::hardware_concurrency();

  vector<thread> threads;
  threads.reserve(number_of_threads);

  for (int i = 0; i < number_of_threads; i++) {
    threads.emplace_back(thread(generate, ref(*this), i));
  }

  for (auto &thread: threads) {
    thread.join();
  }

  if (gettimeofday(&tv2, nullptr) != 0) {
    perror("gettimeofday");
    exit(EXIT_FAILURE);
  }

  double time_spent = timevalsub(&tv1, &tv2);

  cout << "Generated puzzle in " << time_spent << endl;
}

void generate(Generator &generator, int n) {
  while (true) {
    Situation initial_situation;

    while (initial_situation.cars.size() < generator.number_of_cars) {
      Car new_car;

      if (initial_situation.cars.empty()) {
        new_car = Car(target_line_range(generator.random_generator),
                      SIZE - 2,
                      2,
                      Plane::HORIZONTAL);
      } else {
        new_car = Car(position_range(generator.random_generator),
                      position_range(generator.random_generator),
                      length_range(generator.random_generator),
                      direction_range
                          (generator.random_generator) ? Plane::HORIZONTAL
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

    Explorer explorer(initial_situation, generator.range.end);

    int tries;

    {
      std::unique_lock<std::mutex> lk(generator.m);

      tries = generator.tries;

      ++generator.tries;

      if (explorer.is_solved() && generator.range.is_between(explorer.moves)) {
        generator.generating = false;
        explorer.solution->situation.save("../assets/generated_puzzles/" + to_string(generator.difficulty_level) +
            "_" + to_string(explorer.moves) + "_" + to_string(generator.number_of_cars) + "_" + to_string(explorer
                                                                                                              .time_spent)
                                              + ".txt");
        cout << "[Thread " << n << "] Try " << generator.tries << " : " << "Generated a solvable puzzle in "
             << explorer.moves
             << " moves, "
             << explorer.time_spent
             << "s)"
             << endl;
        explorer.print();
      }

      if (!generator.generating) {
        break;
      }
    }
  }
}
