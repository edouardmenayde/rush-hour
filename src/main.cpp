#include <iostream>
#include "Situation.h"
#include "Explorer.h"
#include "Generator.h"

int main(int argc, char *argv[]) {
  vector<string> args(argv + 1, argv + argc);

  if (args.size() == 2 && args.at(0) == "-i") {
    Situation test(args.at(1));
    Explorer explorer(test);
    explorer.print();
  } else if (args.size() == 2 && args.at(0) == "-g") {
    Generator(stoi(args.at(1)));
  } else if (args.size() == 1 && args.at(0) == "-v") {
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
         << "- ./rush-hour -i <file_path>" << endl
         << "- ./rush-hour -g <difficulty_level>" << endl
         << "- ./rush-hour -v" << endl;
  }

  return 0;
}
