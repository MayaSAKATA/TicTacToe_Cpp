#include "TicTacToe.hpp"

using namespace std;

int main()
{
    int choice;
    cout << "Select difficulty level:\n1. Easy (human vs human)\n2. Medium (human vs computer)\n3. Hard (not implemented)\n"
         << endl;
    cout << "Enter your choice (1-2): " << endl;
    cin >> choice;
    while (choice < 1 || choice > 2)
    {
        cout << "Only two levels available 1 or 2" << endl;
        cin >> choice;
    }

    TicTacToe Game = TicTacToe(choice);

    cout << "Let's play\n " << endl;

    bool continue_game = true;
    while (continue_game)
    {
        continue_game = Game.Play();
    }

    return 0;
}