#include "TicTacToe.hpp"

using namespace std;


int main()
{
    TicTacToe Game; 
    Game.Stockage();
    Game.displayBoard();

    // After evrey play the player automaticaly
    // A play consist to give the position 

    Game.Play(0, 1);    // X 
    Game.Play(1, 1);    // O
    Game.Play(2, 1);   
    Game.Play(1, 2);
    Game.Play(0, 0);
    Game.Play(2, 0);
    Game.Play(2, 2);
    Game.Play(1, 0);
    Game.Play(0, 2);

    
    Game.displayBoard();

    return 0;
}