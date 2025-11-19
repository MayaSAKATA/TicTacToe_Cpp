#include "TicTacToe.hpp"

using namespace std;

// Constructor
TicTacToe::TicTacToe(){

}

// Stockage 
void TicTacToe::Stockage(){
<<<<<<< Updated upstream
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            Board[i][j] = '_';
}
    
// Function to print the DashBoard
void TicTacToe::DashBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
=======
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
>>>>>>> Stashed changes
            std::cout << "["<< Board[i][j] << "] ";
        std::cout << std::endl;
    }
}

// Function to switch player
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
void TicTacToe::Switchplayer(){
    if(current_player == 'X')
        current_player = 'O';
    else 
        current_player = 'X';
}

// Function to play
<<<<<<< Updated upstream
bool TicTacToe::Play(int line, int col){
    if(Board[line][col] == '_'){
=======

bool TicTacToe::Play(int line, int col){
    // Assign the position if it's free else Nothing 
    if(Board[line][col] == '_'){          
>>>>>>> Stashed changes
        Board[line][col] = current_player;
        Switchplayer();
        return true;
    }else{
        return false;
    }
}


<<<<<<< Updated upstream
// Function to show the win
=======
// Function to show the win // On it
>>>>>>> Stashed changes
void TicTacToe::Win(int line, int col, char current_player){

    // Horizontal Win


    // Vertical Win


    // First Diagonal Win


    // Second Diagonal Win


}