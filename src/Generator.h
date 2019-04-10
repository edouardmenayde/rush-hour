#ifndef RUSH_HOUR_GENERATOR_H
#define RUSH_HOUR_GENERATOR_H

#include <random>
#include <thread>
#include <mutex>

using namespace std;

/**
 * Values authorized between `start` and `end` both included.
 */
class Range {
 public:
  int start = 0;
  int end = 0;

  Range(int s, int e) : start(s), end(e) {};
  Range() = default;

  bool is_between(int m);
};

/**
 * Generates one or more situation fitting constraint for the selected level (between 1 and 4 included).
 */
class Generator {
 public:
  mt19937 random_generator;
  uint8_t number_of_cars;
  mutex m;
  Range range;
  bool generating = true;
  int tries = 1;
  const int difficulty_level;
  string output_path;

  explicit Generator(uint8_t difficulty_level, string &output_path);
};

void generate(Generator &generator, int n);

#endif //RUSH_HOUR_GENERATOR_H
