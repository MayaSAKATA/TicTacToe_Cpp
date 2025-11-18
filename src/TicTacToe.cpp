#include "TicTacToe.hpp"

TicTacToe::TicTacToe() : board({'1', '2', '3', '4', '5', '6', '7', '8', '9'})
{
    grid_size = 3;
}

void TicTacToe::displayBoard()
{
    cout << "\nTicTacToe\n\n";
    cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << " " << endl;
    cout << "-----" << "|" << "-----" << "|" << "-----" << endl;
    cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << " " << endl;
    cout << "-----" << "|" << "-----" << "|" << "-----" << endl;
    cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << " " << endl;
}