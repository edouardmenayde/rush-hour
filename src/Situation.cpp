#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Situation.h"
#include "deps/termcolor.hpp"

// Move

bool Move::operator==(const Move &rhs) const {
    return car_index == rhs.car_index &&
           direction == rhs.direction;
}

bool Move::operator!=(const Move &rhs) const {
    return !(rhs == *this);
}

ostream &operator<<(ostream &os, const Move &move) {
    os << "(" << move.car_index << ", " << move.direction << ", " << move.steps << ")";
    return os;
}

// Situation

Situation::Situation(string filename) {
    ifstream file;

    file.open(filename);

    if (file.fail()) {
        cerr << "Could not read file `" << filename << "`." << endl;
    }

    string line;

    unsigned int x_exit, y_exit;

    file >> x_exit >> y_exit; // First line consist of the exit coordinates

    exit = Vector2{x_exit, y_exit};

    int line_pos, column_pos, length;
    bool horizontal;

    while (file >> line_pos >> column_pos >> length >> horizontal) {
        cars.push_back(Car{
                line_pos, column_pos, length, horizontal ? HORIZONTAL : VERTICAL
        });
    }

    file.close();

    compute_parking();
}

void Situation::print() {
    const string alphabet = "=BCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (parking[i][j] == -1) {
                cout << "  ";
            } else if (parking[i][j] == 0) {
                cout << termcolor::yellow << termcolor::bold << alphabet[parking[i][j]] << termcolor::reset << " ";
            } else {
                cout << alphabet[parking[i][j]] << " ";
            }
        }
        if (i + 1 < SIZE) {
            cout << endl;
        }
    }
}

void Situation::print(Move &move) {
    const string alphabet = "=BCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (parking[i][j] == -1) {
                cout << "  ";
            } else if (parking[i][j] == 0) {
                cout << termcolor::blue << termcolor::bold << alphabet[parking[i][j]] << termcolor::reset << " ";
            } else if (parking[i][j] == move.car_index) {
                cout << termcolor::yellow << termcolor::bold << alphabet[parking[i][j]] << termcolor::reset << " ";
            } else {
                cout << alphabet[parking[i][j]] << " ";
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
        if (car.plane == VERTICAL) {
            if (car.line - 1 >= 0 && parking[car.line - 1][car.column] == -1) {
                //We can move UP
                moves.push_back(Move{car_number, UP, 1});
                if (car.line - 2 >= 0 && parking[car.line - 2][car.column] == -1) {
                    moves.push_back(Move{car_number, UP, 2});
                    if (car.line - 3 >= 0 && parking[car.line - 3][car.column] == -1) {
                        moves.push_back(Move{car_number, UP, 3});
                        if (car.line - 4 >= 0 && parking[car.line - 4][car.column] == -1) {
                            moves.push_back(Move{car_number, UP, 4});
                            if (car.line - 5 >= 0 && parking[car.line - 5][car.column] == -1) {
                                moves.push_back(Move{car_number, UP, 5});
                            }
                        }
                    }
                }
            }
            if (car.line + 1 <= SIZE && parking[car.line + car.length - 1 + 1][car.column] == -1) {
                //We can move DOWN
                moves.push_back(Move{car_number, DOWN, 1});
                if (car.line + 2 <= SIZE && parking[car.line + car.length - 1 + 2][car.column] == -1) {
                    moves.push_back(Move{car_number, DOWN, 2});
                    if (car.line + 3 <= SIZE && parking[car.line + car.length - 1 + 3][car.column] == -1) {
                        moves.push_back(Move{car_number, DOWN, 3});
                        if (car.line + 4 <= SIZE && parking[car.line + car.length - 1 + 4][car.column] == -1) {
                            moves.push_back(Move{car_number, DOWN, 4});
                            if (car.line + 5 <= SIZE && parking[car.line + car.length - 1 + 5][car.column] == -1) {
                                moves.push_back(Move{car_number, DOWN, 5});
                            }
                        }
                    }
                }
            }
        } else {
            if (car.column - 1 >= 0 && parking[car.line][car.column - 1] == -1) {
                //We can move LEFT
                moves.push_back(Move{car_number, LEFT, 1});
                if (car.column - 2 >= 0 && parking[car.line][car.column - 2] == -1) {
                    moves.push_back(Move{car_number, LEFT, 2});
                    if (car.column - 3 >= 0 && parking[car.line][car.column - 3] == -1) {
                        moves.push_back(Move{car_number, LEFT, 3});
                        if (car.line - 4 >= 0 && parking[car.line][car.column - 4] == -1) {
                            moves.push_back(Move{car_number, LEFT, 4});
                            if (car.line - 5 >= 0 && parking[car.line][car.column - 5] == -1) {
                                moves.push_back(Move{car_number, LEFT, 5});
                            }
                        }
                    }
                }
            }
            if (car.column + 1 <= SIZE && parking[car.line][car.column + car.length - 1 + 1] == -1) {
                //We can move RIGHT
                moves.push_back(Move{car_number, RIGHT, 1});
                if (car.column + 2 <= SIZE && parking[car.line][car.column + car.length - 1 + 2] == -1) {
                    moves.push_back(Move{car_number, RIGHT, 2});
                    if (car.column + 3 <= SIZE && parking[car.line][car.column + car.length - 1 + 3] == -1) {
                        moves.push_back(Move{car_number, RIGHT, 3});
                        if (car.column + 4 <= SIZE && parking[car.line][car.column + car.length - 1 + 4] == -1) {
                            moves.push_back(Move{car_number, RIGHT, 4});
                            if (car.column + 5 <= SIZE && parking[car.line][car.column + car.length - 1 + 5] == -1) {
                                moves.push_back(Move{car_number, RIGHT, 5});
                            }
                        }
                    }
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
        if (car.plane == HORIZONTAL) {
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

Situation::Situation(
        const Situation &old_situation,
        const Move &move) {
    copy(old_situation.cars.begin(), old_situation.cars.end(), back_inserter(cars));

    auto &car = cars[move.car_index];

    switch (move.direction) {
        case UP:
            car.line -= move.steps;
            break;
        case DOWN:
            car.line += move.steps;
            break;
        case RIGHT:
            car.column += move.steps;
            break;
        case LEFT:
            car.column -= move.steps;
            break;
        default:
            perror("Unrecognized move");
    }

    exit = old_situation.exit;

    compute_parking();
}

bool Situation::is_solution() {
    return parking[exit.line][exit.column] == TARGET_CAR_INDEX;
}

bool Situation::operator==(const Situation &rhs) const {
    return std::equal(cars.begin(), cars.end(), rhs.cars.begin());
}

bool Situation::operator!=(const Situation &rhs) const {
    return !(rhs == *this);
}

Situation &Situation::operator=(const Situation &old_situation) {
    copy(old_situation.cars.begin(), old_situation.cars.end(), back_inserter(this->cars));
    exit = old_situation.exit;
    compute_parking();

    return *this;
}

