#include "catch.hpp"
#include "../src/Situation.h"

TEST_CASE("Puzzle is imported without error") {
  Situation test("../test/support/puzzle.txt");
}

TEST_CASE("Compute moves from a situation") {
  Situation test("../test/support/puzzle.txt");

  vector<Move> expected_moves = {
      Move{2, DOWN},  // 0 2 3 1
      Move{4, DOWN},  // 1 3 2 0
      Move{7, RIGHT}, // 3 0 2 1
      Move{9, UP},    // 4 3 2 0
      Move{10, UP},   // 4 4 2 0
  };

  test.compute_moves();

  REQUIRE(test.moves == expected_moves);
}

TEST_CASE("Compute parking from a situation") {
  Situation test("../test/support/puzzle.txt");

  array<array<int, SIZE>, SIZE> expected_parking = {
      {
          {
              1, -1, 2, 3, 3, 3
          },
          {
              1, -1, 2, 4, 5, 5
          },
          {
              0, 0, 2, 4, -1, 6
          },
          {
              7, 7, -1, -1, -1, 6
          },
          {
              8, -1, -1, 9, 10, 11
          },
          {
              8, 12, 12, 9, 10, 11
          }
      }
  };

  test.compute_parking();

  REQUIRE(test.parking == expected_parking);
}

TEST_CASE("Can move a car") {
  Situation test("../test/support/puzzle.txt");

  Situation test2 = test.move(Move{7, RIGHT});

  REQUIRE(test2.cars[7].column == 1);
}


TEST_CASE("A situation can be solved") {
  Situation test("../test/support/solved.txt");

  REQUIRE(test.is_solution());
}
