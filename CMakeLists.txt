cmake_minimum_required(VERSION 3.10)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

find_package(Catch2 3 REQUIRED)

include_directories(include)
add_library(TicTacToe src/TicTacToe.cpp)

add_executable(test_TicTacToe tests/test_TicTacToe.cpp)
target_link_libraries(test_TicTacToe TicTacToe Catch2::Catch2WithMain)