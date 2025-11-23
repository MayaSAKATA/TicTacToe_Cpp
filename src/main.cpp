#include "TicTacToe.hpp"

using namespace std;

int askChoice()
{
    while (true)
    {
        int choice;
        cout << "Chose a position : " << endl;
        cin >> choice;
        if (choice < 1 || choice > 9)
        {
            cout << "Choice of of range (1-9). Retry." << endl;
            continue;
        }
        return choice;
    }
}

int main()
{
    TicTacToe Game = TicTacToe();

    cout << "Let's play\n " << endl;
    Game.displayBoard();

    int choice, row, col;

    do
    {
        choice = askChoice();
        row = (choice - 1) / 3;
        col = (choice - 1) % 3;
    } while (Game.Play(row, col));

    return 0;
}