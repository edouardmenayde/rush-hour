#include <iostream>
#include "Situation.h"
#include "Explorer.h"
#include "Generator.h"

int main() {
  Situation test("../test/support/puzzle.txt");
  Explorer explorer(test);
  explorer.print();
//  Generator generator(4);

  cout << "uint8: " << sizeof(uint8_t) << "B" << endl;
  cout << "int8: " << sizeof(int8_t) << "B" << endl;
  cout << "Direction: " << sizeof(Direction) << "B" << endl;
  cout << "Move: " << sizeof(Move) << "B" << endl;
  cout << "Moves: " << sizeof(Moves) << "B" << endl;
  cout << "Plane: " << sizeof(Plane) << "B" << endl;
  cout << "Car: " << sizeof(Car) << "B" << endl;
  cout << "Vector2: "<< sizeof(Vector2) << "B" << endl;
  cout << "Parking: " << sizeof(Parking) << "B" << endl;
  cout << "Cars: " <<sizeof(Cars) << "B" << endl;
  cout << "Situation: " << sizeof(Situation) << "B" << endl;

  return 0;
}
