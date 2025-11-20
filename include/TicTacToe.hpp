#ifndef TICTACTOE_HPP 
#define TICTACTOE_HPP

#include <iostream>
#include <vector>

using namespace std;

class TicTacToe{
    static const int grid_size = 3; // Static definition of the grid

    // Definition of the board using a double-entry table
    char Board[grid_size][grid_size] = { 
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    // Declaration and initialisation of the player
    char current_player = 'X';

public:
    TicTacToe(); // Constructor

    void Stockage(); // Function to store every game in the Board 

    void  displayBoard(); // Function to print the Board

    bool Play(int line, int col); // Function to Select the positon of a play

    void Switchplayer();  // function to switch automaticaly the player

    bool Win(int line, int col, char current_player); // Function to check a win after a game

    bool Tie(); // Function to chek the Tie
    

};


#endif


