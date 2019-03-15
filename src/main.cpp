#include <iostream>
#include "Situation.h"
#include "Explorer.h"

int main() {
  Situation test("../test/support/puzzle.txt");
  Explorer explorer(test);

  return 0;
}
