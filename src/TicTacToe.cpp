#include "TicTacToe.hpp"

using namespace std;

// Constructor
TicTacToe::TicTacToe(){

}

// Stockage 
void TicTacToe::Stockage(){
    for (int i = 0; i < TicTacToe::grid_size; i++){
        for (int j = 0; j < TicTacToe::grid_size; j++){
            Board[i][j] = '_';
        }
    }
}

// Function to print the Board

void TicTacToe::displayBoard(){
     for (int i = 0; i < TicTacToe::grid_size; i++) {
        for (int j = 0; j < TicTacToe::grid_size; j++)

            std::cout << "["<< Board[i][j] << "] ";
        std::cout << std::endl;
    }
}

// Function to switch player

void TicTacToe::Switchplayer(){
    if(current_player == 'X')
        current_player = 'O';
    else 
        current_player = 'X';
}

// Function to play

bool TicTacToe::Play(int line, int col){
    // Assign the position if it's free else Nothing 
    if(Board[line][col] == '_'){          
        Board[line][col] = current_player;
        Switchplayer();
        return true;
    }else{
        return false;
    }
}


// Function to show the win // On it

void TicTacToe::Win(int line, int col, char current_player){

    // Horizontal Win


    // Vertical Win


    // First Diagonal Win


    // Second Diagonal Win


}