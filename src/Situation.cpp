#include <fstream>
#include <iostream>
#include "Situation.h"


Situation Situation::from_file(string filename) {
    ifstream file;

    file.open(filename);

    if (file.fail()) {
        cerr << "Could not read file `" << filename << "`." << endl;
    }

    Situation situation;

    string line;

    unsigned int x_exit, y_exit;

    file >> x_exit >> y_exit; // First line consist of the exit coordinates

    situation.exit = Vector2{x_exit, y_exit};

    unsigned int line_pos, column_pos, length;
    bool horizontal;

    bool target = true;

    while (file >> line_pos >> column_pos >> length >> horizontal) {
        Plan plan = horizontal ? HORIZONTAL : VERTICAL;
        Car car = {
                line_pos, column_pos, length, plan, target
        };
        situation.cars.push_back(car);
        target = false; // After the first pass the following cars are not the target
    }

    file.close();

    return situation;
}

void Situation::print() {
    const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    compute_parking();

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (!parking[i][j]) {
                cout << "  ";
            } else {
                cout << alphabet[parking[i][j] - 1] << " ";
            }
        }
        if (i + 1 < SIZE) {
            cout << endl;
        }
    }
}

void Situation::compute_moves() {
    unsigned int car_number = 0;
    for (auto &car : cars) {
        if (car.plan == VERTICAL) {
            if (car.line - 1 >= 0) {
                // We can move UP
                int new_line = car.line - 1;
                if (parking[new_line][car.column]) {
                    moves.push_back(Move{car_number, UP});
                }
            }
            if (car.line + car.length + 1 < SIZE) {
                // We can move DOWN
                int new_line = car.line + 1 + car.length;
                if (parking[new_line][car.column]) {
                    moves.push_back(Move{car_number, DOWN});
                }
            }
        } else {
            if (car.column - 1 >= 0) {
                // We can move to the LEFT
                int new_column = car.column - 1;
                if (parking[car.line][new_column]) {
                    moves.push_back(Move{car_number, LEFT});
                }
            }
            if (car.column + car.length + 1 < SIZE) {
                // We can move to the RIGHT
                int new_column = car.column + 1 + car.length;
                if (parking[car.line][new_column]) {
                    moves.push_back(Move{car_number, RIGHT});
                }
            }
        }
        car_number++;
    }
}

void Situation::compute_parking() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            parking[i][j] = -1;
        }
    }

    unsigned int car_number = 0;

    for (auto &car : cars) {
        if (car.direction == HORIZONTAL) {
            for (int i = 0; i < car.length; i++) {
                parking[car.line][car.column + i] = car_number;
            }
        } else {
            for (int i = 0; i < car.length; i++) {
                parking[car.line + i][car.column] = car_number;
            }
        }
        car_number++;
    }
}
