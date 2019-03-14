#ifndef RUSH_HOUR_SITUATION_H
#define RUSH_HOUR_SITUATION_H

#include <vector>
#include "Vector2.h"
#include "Car.h"
#include <string>
#include "Direction.h"

using namespace std;

struct Move {
    unsigned int car_index;
    Direction direction;
};

const unsigned int SIZE = 6;


/**
 * A parking situation with all the cars in it and the exit.
 */
class Situation {
public:

    /**
     * Array containing all the cars in the parking including the one we want to move to the exit which is represented by a boolean.
     */
    std::vector<Car> cars;

    /**
     * Represents the exit of the parking in 2D space.
     */
    Vector2 exit;

    vector<Move> moves;

    int parking[SIZE][SIZE];

    void print();

    static Situation from_file(string filename);

    void compute_moves();

    void compute_parking();
};

#endif //RUSH_HOUR_SITUATION_H
