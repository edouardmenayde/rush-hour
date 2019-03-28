#include <iostream>
#include "Situation.h"
#include "Explorer.h"

int main() {
  Situation test("../test/support/puzzle.txt");
  Explorer explorer(test);

  cout << "Plane: " << sizeof(Plane) << "B" << endl;
  cout << "Direction: " << sizeof(Direction) << "B" << endl;
  cout << "Car: " << sizeof(Car) << "B" << endl;
  cout << "Move: " << sizeof(Move) << "B" << endl;
  cout << "Vector2: "<< sizeof(Vector2) << "B" << endl;
  cout << "Parking: " << sizeof(Parking) << "B" << endl;
  cout << "Cars: " <<sizeof(Cars) << "B" << endl;
  cout << "Situation: " << sizeof(Situation) << "B" << endl;

  return 0;
}
