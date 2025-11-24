#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <iostream>
#include <vector>
#include <cstdlib> // For rand() function

using namespace std;

class TicTacToe
{
    static const int grid_size = 3; // Static definition of the grid

    // Definition of the board using a double-entry table
    char Board[grid_size][grid_size] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

    // Declaration and initialisation of the player
    char current_player = 'X';
    int difficulty; // 1: easy, 2: medium, 3: hard

public:
    TicTacToe(int difficulty); // Constructor

    void displayBoard(); // Function to print the board

    std::vector<std::pair<int, int>> getEmptyCells(); // Function to get empty cells

    std::pair<int, int> getComputerMove(); // Function to get the computer's move based on difficulty

    void Switchplayer(); // Function to switch automaticaly the player

    bool Win(int row, int col, char current_player); // Function to check a win after a game

    bool Tie(); // Function to check the Tie

    bool Play(); // Function to Select the positon of a play
};

#endif
