#include <iostream>
#include <cassert>

using namespace std;

#include "../src/Explorer.h"

int main() {

  cout << "Starting tests..." << endl;

  Situation test = Situation::from_file("../test/support/puzzle.txt");

  test.print();

  Explorer explorer(test);

  return 0;
}
