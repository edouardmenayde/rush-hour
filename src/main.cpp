#include <iostream>
#include "Situation.h"
#include "Explorer.h"
#include "Generator.h"

int main(int argc, char *argv[]) {
  vector<string> args(argv + 1, argv + argc);

  if (args.size() == 2 && args.at(0) == "solve") {
    Situation test(args.at(1));
    Explorer explorer(test);
    explorer.print();
  } else if (args.size() == 3 && args.at(0) == "generate") {
    Generator(stoi(args.at(1)), args.at(2));
  } else if (args.size() == 1 && args.at(0) == "info") {
    cout << "uint8: " << sizeof(uint8_t) << "B" << endl;
    cout << "int8: " << sizeof(int8_t) << "B" << endl;
    cout << "Direction: " << sizeof(Direction) << "B" << endl;
    cout << "Move: " << sizeof(Move) << "B" << endl;
    cout << "Moves: " << sizeof(Moves) << "B" << endl;
    cout << "Plane: " << sizeof(Plane) << "B" << endl;
    cout << "Car: " << sizeof(Car) << "B" << endl;
    cout << "Vector2: " << sizeof(Vector2) << "B" << endl;
    cout << "Parking: " << sizeof(Parking) << "B" << endl;
    cout << "Cars: " << sizeof(Cars) << "B" << endl;
    cout << "Situation: " << sizeof(Situation) << "B" << endl;
  } else {
    cout << "Usage :" << endl
         << "- ./rush-hour solve <file_path>" << endl
         << "- ./rush-hour generate <difficulty_level> <output_path>" << endl
         << "- ./rush-hour info" << endl;
  }

  return 0;
}
