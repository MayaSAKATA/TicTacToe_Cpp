#ifndef TICTACTOE_HPP 
#define TICTACTOE_HPP

#include <iostream>
#include <vector>

using namespace std;

class TicTacToe{
    private:

        static const int Taille = 3;
        char Board[Taille][Taille] = { 
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        } ;
        char current_player = 'X';

    public:

    TicTacToe();
    void Stockage();
    void  DashBoard();
    bool Play(int line, int col);
    void Switchplayer();
    void Win(int line, int col, char current_player);

    
};



#endif


