#ifndef RUSH_HOUR_GENERATOR_H
#define RUSH_HOUR_GENERATOR_H

#include <random>
#include <array>

using namespace std;

class Range {
 public:
  int start = 0;
  int end = 0;

  Range(int s, int e) : start(s), end(e) {};
  Range() {};

  bool is_between(int m);
};

class Generator {
 private:
  mt19937 generator;
  uint8_t number_of_cars;

 public:
  explicit Generator(uint8_t difficulty_level);
};

#endif //RUSH_HOUR_GENERATOR_H
