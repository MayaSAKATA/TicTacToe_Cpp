#include "TicTacToe.hpp"

using namespace std;

int main()
{
    int players, level, number_of_games;
    cout << "Welcome to Tic Tac Toe!\n";
    cout << "=======================\n";

    cout << "How many players?\n1. Two Players (Human vs Human)\n2. One Player (vs Computer)\n";
    cin >> players;
    while (players < 1 || players > 2)
    {
        cout << "Only two options available 1 or 2" << endl;
        cin >> players;
    }
    if (players == 2)
    {
        cout << "\nSelect difficulty level:\n1. Easy\n2. Hard (not implemented)\nEnter your choice (1-2): ";
        cin >> level;
        while (level < 1 || level > 2)
        {
            cout << "Only two levels available 1 or 2" << endl;
            cin >> level;
        }
    }
    else
    {
        level = 0; // Two players mode
    }
    cout << "\nHow many games in row? ";
    cin >> number_of_games;

    TicTacToe Game = TicTacToe(level, number_of_games);

    cout << "\nLet's play !\n " << endl;

    Game.Session(number_of_games);

    return 0;
}