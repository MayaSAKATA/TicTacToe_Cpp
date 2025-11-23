#include "TicTacToe.hpp"

using namespace std;

// Constructor
TicTacToe::TicTacToe()
{
    // Initialize the board with empty positions
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++)
            Board[i][j] = '_';

    current_player = 'X';
}

// Function to display the board on the console

void TicTacToe::displayBoard()
{
    int num = 1; // empty cell numbering starts from 1
    for (int i = 0; i < TicTacToe::grid_size; i++)
    {
        for (int j = 0; j < TicTacToe::grid_size; j++)
        {
            // Displays the cell content or its number if empty
            char c = (Board[i][j] == '_') ? ('0' + num) : Board[i][j];
            cout << " " << c << " ";
            if (j < TicTacToe::grid_size - 1)
                cout << "|";
            num++;
        }
        cout << endl;
        if (i < TicTacToe::grid_size - 1)
            cout << "---+---+---" << endl; // separator between rows
    }
    cout << endl;
}

// Function to switch the current player

void TicTacToe::Switchplayer()
{
    if (current_player == 'X')
        current_player = 'O'; // Switch from X to O
    else
        current_player = 'X'; // Switch from O to X
}

// Function to check if the current player has won

bool TicTacToe::Win(int row, int col, char current_player)
{

    // Check for horizontal win on the current line
    bool win_line = true;
    for (int c = 0; c < TicTacToe::grid_size; c++)
    {
        if (Board[row][c] != current_player)
        {                     // If any cell is not current player
            win_line = false; // Horizontal win not possible
            break;
        }
    }
    if (win_line)
    {
        return true; // Player wins horizontally
    }

    // Check for vertical win on the current column
    bool win_col = true;
    for (int l = 0; l < TicTacToe::grid_size; l++)
    {
        if (Board[l][col] != current_player)
        {                    // If any cell is not current player
            win_col = false; // Vertical win not possible
            break;
        }
    }
    if (win_col)
    {
        return true; // Player wins vertically
    }

    // Check for first diagonal (\)
    if (row == 0 && col == 0)
    {
        if ((Board[row + 1][col + 1] == current_player) && (Board[row + 2][col + 2] == current_player))
        {
            return true; // Top-left to bottom-right diagonal win
        }
    }

    if (row == 1 && col == 1)
    {
        if ((Board[row - 1][col - 1] == current_player) && (Board[row + 1][col + 1] == current_player))
        {
            return true; // Middle diagonal check
        }
    }

    if (row == 2 && col == 2)
    {
        if ((Board[row - 1][col - 1] == current_player) && (Board[row - 2][col - 2] == current_player))
        {
            return true; // Bottom-right diagonal check
        }
    }

    // Check for second diagonal (/)
    if (row == 2 && col == 0)
    {
        if ((Board[row - 1][col + 1] == current_player) && (Board[row - 2][col + 2] == current_player))
        {
            return true; // Bottom-left to top-right diagonal win
        }
    }

    if (row == 1 && col == 1)
    {
        if ((Board[row + 1][col - 1] == current_player) && (Board[row - 1][col + 1] == current_player))
        {
            return true; // Middle diagonal check
        }
    }

    if (row == 0 && col == 2)
    {
        if ((Board[row + 1][col - 1] == current_player) && (Board[row + 2][col - 2] == current_player))
        {
            return true; // Top-right diagonal check
        }
    }

    // No win detected
    return false;
}

// Function to check for a Tie (all cells filled and no winner)

bool TicTacToe::Tie()
{
    for (int i = 0; i < TicTacToe::grid_size; i++)
    {
        for (int j = 0; j < TicTacToe::grid_size; j++)
        {
            if (Board[i][j] == '_')
            {
                return false; // At least one empty cell -> not a tie
            }
        }
    }
    return true; // All cells are filled
}

// Function to play a turn at the given position
bool TicTacToe::Play(int line, int col)
{
    // Only allow move if the cell is empty
    if (Board[line][col] == '_')
    {
        Board[line][col] = current_player; // Place current player's mark

        // Check if this move wins the game
        if (Win(line, col, current_player))
        {
            displayBoard();              // Show the final board
            cout << " YOU WIN " << endl; // Announce victory
            return false;                // Stop the game
        }

        // Check for Tie
        if (Tie())
        {
            displayBoard();
            cout << " It is a tie, play again!" << endl; // Tie message
            return false;                                // Stop the game
        }

        displayBoard(); // Show board after move
        Switchplayer(); // Switch to the next player
        return true;    // Continue game
    }
    else
    {
        return false; // Invalid move, cell already occupied
    }
}
