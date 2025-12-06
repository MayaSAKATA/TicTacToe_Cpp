cmake_minimum_required(VERSION 3.10)

project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)
if(APPLE)
    list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
    include_directories("/opt/homebrew/include")
    link_directories("/opt/homebrew/lib")
endif()

find_package(Catch2 3 REQUIRED)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

include_directories(include)

add_library(TicTacToe src/TicTacToe.cpp)
target_link_libraries(TicTacToe PUBLIC SFML::Graphics SFML::Window SFML::System)

add_library(Graphics src/Graphics.cpp)
target_link_libraries(Graphics PUBLIC TicTacToe SFML::Graphics SFML::Window SFML::System)

add_executable(PlayTicTacToe src/main.cpp)
target_link_libraries(PlayTicTacToe PRIVATE 
    TicTacToe 
    Graphics 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)

add_executable(test_TicTacToe tests/test_TicTacToe.cpp)
target_link_libraries(test_TicTacToe TicTacToe Catch2::Catch2WithMain)