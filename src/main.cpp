#include "TicTacToe.hpp"

using namespace std;


int main()
{
    TicTacToe Game; 
    Game.Stockage();
    Game.displayBoard();

    // After evrey play the player automaticaly
    // A play consist to give the position 
    // Ask a player to to play

    int line, col;
    cout << "Give the position: " << endl;
    cin >> line >> col;

    while (Game.Play(line, col)){

        cout << "Give the position: " << endl;
        cin >> line >> col;
        
    } 

    return 0;
}