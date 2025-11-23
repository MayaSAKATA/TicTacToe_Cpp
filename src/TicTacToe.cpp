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
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            // Displays the cell content or its number if empty
            char c = (Board[i][j] == '_') ? ('0' + num) : Board[i][j];
            cout << " " << c << " ";
            if (j < grid_size - 1)
                cout << "|";
            num++;
        }
        cout << endl;
        if (i < grid_size - 1)
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
    for (int c = 0; c < grid_size; c++)
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
    for (int l = 0; l < grid_size; l++)
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

    // Check the main diagonal on the current column
    if (row == col)
    {
        bool winDiag1 = true;
        for (int i = 0; i < grid_size; i++)
        {
            if (Board[i][i] != current_player)
            {
                winDiag1 = false;
                break;
            }
        }
        if (winDiag1)
            return true;
    }

    // Check the anti-diagonal on the current column
    if (row + col == grid_size - 1)
    {
        bool winDiag2 = true;
        for (int i = 0; i < grid_size; i++)
        {
            if (Board[i][grid_size - 1 - i] != current_player)
            {
                winDiag2 = false;
                break;
            }
        }
        if (winDiag2)
            return true;
    }

    // No win detected
    return false;
}

// Function to check for a Tie (all cells filled and no winner)

bool TicTacToe::Tie()
{
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
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
    if (Board[line][col] != '_')
        return false;

    Board[line][col] = current_player;

    displayBoard();

    if (Win(line, col, current_player)) // Check if this move wins the game
    {
        cout << " YOU WIN " << endl; // Announce victory
        return false;                // Stop the game
    }

    if (Tie()) // Check for Tie
    {
        cout << " It is a tie, play again!" << endl; // Tie message
        return false;                                // Stop the game
    }

    Switchplayer(); // Switch to the next player
    return true;    // Continue game
}
