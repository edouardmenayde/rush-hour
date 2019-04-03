#include "catch.hpp"
#include "../src/Explorer.h"

TEST_CASE("Can solve base problem") {
  Situation test("../test/support/puzzle.txt");
  Explorer explorer(test);

  REQUIRE(explorer.moves == 14);
  REQUIRE(explorer.time_spent <= 0.5);
}