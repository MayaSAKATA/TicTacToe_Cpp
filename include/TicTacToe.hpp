#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <vector>
#include <iostream>
using namespace std;

class TicTacToe
{

private:
    int grid_size = 3;
    std::vector<char> board;

public:
    TicTacToe(); // Constructor
    void displayBoard();
};

#endif