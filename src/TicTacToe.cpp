/**
 * @file TicTacToe.cpp
 * @brief Implementation of the TicTacToe class methods.
 * @details Contains the logic for board rendering, move validation,
 * computer moves algorithms, and game loop management.
 */

#include "TicTacToe.hpp"

using namespace std;

/**
 * @brief Constructor for the TicTacToe class.
 * * Initializes the board with underscores ('_'), sets the starting player to 'X',
 * and seeds the random number generator.
 * * @param level The difficulty level chosen by the user (1, 2, or 3).
 */
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

/**
 * @brief Displays the current state of the game board on the console.
 * * Iterates through the grid. If a cell is empty ('_'), it displays a number (1-9)
 * to guide the user. Otherwise, it displays the player symbol ('X' or 'O').
 */
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

/**
 * @brief Switches the turn between players.
 * * Changes the 'current_player' attribute from 'X' to 'O' or vice versa.
 */
void TicTacToe::Switchplayer()
{
    if (current_player == 'X')
        current_player = 'O'; // Switch from X to O
    else
        current_player = 'X'; // Switch from O to X
}

/**
 * @brief Checks if the current player has won the game.
 * * @param row The row index of the move just made.
 * @param col The column index of the move just made.
 * @param current_player The symbol of the player to check for a win.
 * @return true If the move resulted in a winning condition.
 * @return false Otherwise.
 */
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

/**
 * @brief Checks for a tie.
 * * Iterates through the board to see if any empty cells ('_') remain.
 * * @return true If the board is full (no empty cells).
 * @return false If there are still possible moves.
 */
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

/**
 * @brief Identifies all empty cells on the board.
 * * @return std::vector<std::pair<int, int>> A vector containing the coordinates (row, col) of empty cells.
 */
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

/**
 * @brief Determines the computer's move based on difficulty.
 * * - Difficulty 2: Randomly selects an available cell.
 * - Difficulty 3: Optimal strategy.
 * @return std::pair<int, int> The coordinates (row, col) selected by the computer.
 */
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

/**
 * @brief Orchestrates a single turn of the game.
 * * Handles logic for both human input (choices 1-9) and computer moves.
 * Updates the board, checks for win/tie conditions, and switches the player.
 * * @return true If the game should continue to the next turn.
 * @return false If the game has ended (Win or Tie).
 */
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
