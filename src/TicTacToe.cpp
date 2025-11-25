/**
 * @file TicTacToe.cpp
 * @brief Implementation of the TicTacToe class methods.
 * @details Contains the logic for board rendering, move validation,
 * computer moves algorithms, and game loop management.
 */

#include "TicTacToe.hpp"

using namespace std;

TicTacToe::TicTacToe(int level)
{
    current_player = 'X';
    difficulty = level;
    srand(time(0));

    // Initialize the board with empty positions
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++)
            Board[i][j] = '_';
}

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
    cout << '\n'
         << endl;
}

void TicTacToe::Switchplayer()
{
    if (current_player == 'X')
        current_player = 'O'; // Switch from X to O
    else
        current_player = 'X'; // Switch from O to X
}

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

std::vector<std::pair<int, int>> TicTacToe::getEmptyCells()
{
    std::vector<std::pair<int, int>> empty_cells = {};

    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (Board[i][j] == '_')
            {
                empty_cells.push_back(std::make_pair(i, j));
            }
        }
    }
    return empty_cells;
}

std::pair<int, int> TicTacToe::getComputerMove()
{
    if (difficulty == 2)
    {
        std::vector<std::pair<int, int>> empty_cells = getEmptyCells();
        if (!empty_cells.empty()) // check if there are empty cells
        {
            int randomIndex = rand() % empty_cells.size(); // chose a random index to select an empty cell
            return empty_cells[randomIndex];               // returns (row, col) of the selected cell
        }
    }
    if (difficulty == 3)
    {
        // Hard difficulty logic can be implemented here
    }
    return {0, 0};
}
bool TicTacToe::nextGame()
{
    char response;
    cout << "Do you want to continue? (y/n): ";
    cin >> response;
    return (response == 'y' || response == 'Y');
}

bool TicTacToe::Play()
{
    int row, col;
    displayBoard();

    if (difficulty == 1 || current_player == 'X') // corriger ici
    {
        int choice = -1;
        cout << "Chose a position : " << endl;
        cin >> choice;
        cout << '\n';
        while (choice < 1 || choice > 9)
        {
            cout << "Choice of of range (1-9). Chose a position :\n"
                 << endl;
            cin >> choice;
        }

        row = (choice - 1) / grid_size;
        col = (choice - 1) % grid_size;

        if (Board[row][col] != '_')
        {
            cout << "Invalid choice, cell already occupied. Try again.\n"
                 << endl;
            return true; // Continue the game
        }
    }
    else
    {
        // Computer player's turn
        std::pair<int, int> move = getComputerMove();
        row = move.first;
        col = move.second;
        cout << "Computer chose position: " << (row * grid_size + col + 1) << '\n'
             << endl;
    }

    // Place the move on the board
    Board[row][col] = current_player;

    if (Win(row, col, current_player)) // Check if this move wins the game
    {
        displayBoard();
        if (difficulty > 1 && current_player == 'O')
        {
            cout << "COMPUTER WINS\n"
                 << endl; // Announce computer victory
        }
        else
        {
            cout << "YOU WIN\n"
                 << endl; // Announce victory
        }

        return false; // Stop the game
    }

    if (Tie()) // Check for Tie
    {
        displayBoard();
        cout << "It is a tie, play again!\n"
             << endl; // Tie message
        return false; // Stop the game
    }

    Switchplayer(); // Switch to the next player
    return true;    // Continue game
}
