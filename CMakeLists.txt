cmake_minimum_required(VERSION 3.9.2)
project(rush_hour)

set(CMAKE_CXX_STANDARD 17)

set(SRC src/Car.h src/Situation.cpp src/Situation.h src/Vector2.h src/History.cpp
        src/History.h src/Explorer.h src/Explorer.cpp src/Direction.h src/Generator.h src/Generator.cpp
        src/deps/termcolor.hpp src/utils.h src/utils.cpp)

add_executable(rush-hour src/main.cpp ${SRC})
add_executable(rush-hour-tests test/catch.hpp test/test_main.cpp test/test_situation.cpp ${SRC})
