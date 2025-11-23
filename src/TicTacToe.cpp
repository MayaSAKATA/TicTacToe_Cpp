#include "TicTacToe.hpp"

using namespace std;

// Constructor
TicTacToe::TicTacToe(){
    // Initialize the TicTacToe object
    // Nothing specific is done in the constructor for now
}

// Fill the board with empty positions

void TicTacToe::Stockage(){
    for (int i = 0; i < TicTacToe::grid_size; i++){
        for (int j = 0; j < TicTacToe::grid_size; j++){
            Board[i][j] = '_'; // '_' represents an empty cell
        }
    }
}
    

// Function to display the board on the console

void TicTacToe::displayBoard(){
     for (int i = 0; i < TicTacToe::grid_size; i++) {
        for (int j = 0; j < TicTacToe::grid_size; j++)
            cout << "[" << Board[i][j] << "] "; // Print each cell with brackets
        cout << endl; // Move to next line after each row
    }
}


// Function to switch the current player

void TicTacToe::Switchplayer(){
    if(current_player == 'X')
        current_player = 'O'; // Switch from X to O
    else 
        current_player = 'X'; // Switch from O to X
}


// Function to check if the current player has won

bool TicTacToe::Win(int line, int col, char current_player){

    // Check for horizontal win on the current line
    bool win_line = true;
    for (int c = 0; c < TicTacToe::grid_size; c++){
        if (Board[line][c] != current_player){ // If any cell is not current player
            win_line = false; // Horizontal win not possible
            break;
        }
    }
    if(win_line){
        return true; // Player wins horizontally
    }
   
    // Check for vertical win on the current column
    bool win_col = true; 
    for (int l = 0; l < TicTacToe::grid_size; l++){
        if (Board[l][col] != current_player){ // If any cell is not current player
            win_col = false; // Vertical win not possible
            break;
        }
    }
    if(win_col){
        return true; // Player wins vertically
    }

    // Check for first diagonal (\)
    if (line == 0 && col == 0){
        if ((Board[line+1][col+1] == current_player) && (Board[line+2][col+2] == current_player)){
            return true; // Top-left to bottom-right diagonal win
        }
    }

     if (line == 1 && col == 1){
        if ((Board[line-1][col-1] == current_player) && (Board[line+1][col+1] == current_player)){
            return true; // Middle diagonal check
        }
    }

     if (line == 2 && col == 2){
        if ((Board[line-1][col-1] == current_player) && (Board[line-2][col-2] == current_player)){
            return true; // Bottom-right diagonal check
        }
    }

    // Check for second diagonal (/)
    if (line == 2 && col == 0){
        if ((Board[line-1][col+1] == current_player) && (Board[line-2][col+2] == current_player)){
            return true; // Bottom-left to top-right diagonal win
        }
    }

     if (line == 1 && col == 1){
        if ((Board[line+1][col-1] == current_player) && (Board[line-1][col+1] == current_player)){
            return true; // Middle diagonal check
        }
    }

     if (line == 0 && col == 2){
        if ((Board[line+1][col-1] == current_player) && (Board[line+2][col-2] == current_player)){
            return true; // Top-right diagonal check
        }
    }

    // No win detected
    return false;
}


// Function to check for a Tie (all cells filled and no winner)

bool TicTacToe::Tie() {
    for (int i = 0; i < TicTacToe::grid_size; i++) {
        for (int j = 0; j < TicTacToe::grid_size; j++) {
            if (Board[i][j] == '_') {
                return false; // At least one empty cell -> not a tie
            }
        }
    }
    return true; // All cells are filled
}

// Function to play a turn at the given position
bool TicTacToe::Play(int line, int col){
    // Only allow move if the cell is empty
    if(Board[line][col] == '_'){          
        Board[line][col] = current_player; // Place current player's mark

        // Check if this move wins the game
        if (Win(line, col, current_player)){
            displayBoard(); // Show the final board
            cout << " YOU WIN " << endl; // Announce victory
            return false; // Stop the game
        }

        // Check for Tie
        if (Tie()){
            displayBoard();
            cout << " It is a tie, Play again!" << endl; // Tie message
            return false; // Stop the game
        }

        displayBoard(); // Show board after move
        Switchplayer(); // Switch to the next player
        return true; // Continue game
    }else{
        return false; // Invalid move, cell already occupied
    }
}
