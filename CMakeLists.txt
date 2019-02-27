cmake_minimum_required(VERSION 3.13)
project(rush_hour)

set(CMAKE_CXX_STANDARD 17)

add_executable(rush-hour src/main.cpp)
add_executable(rush-hour-tests src/main.cpp test/main.cpp)
