#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <iostream>
#include <vector>

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

public:
    TicTacToe(); // Constructor

    void displayBoard(); // Function to print the board

    bool Play(int row, int col); // Function to Select the positon of a play

    void Switchplayer(); // Function to switch automaticaly the player

    bool Win(int row, int col, char current_player); // Function to check a win after a game

    bool Tie(); // Function to check the Tie
};

#endif
