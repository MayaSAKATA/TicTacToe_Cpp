/**
 * @file TicTacToe.hpp
 * @brief Header file defining the TicTacToe class and its game logic.
 * @author Florient SAKIYE, Maya SAKATA
 * @date 2025
 */

#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
/**
 * @class TicTacToe
 * @brief Main class handling the TicTacToe game logic.
 * * This class manages the game board, player turns, computer moves,
 * and verifies win/tie conditions.
 */

class TicTacToe
{
private:
    /**
     * @brief Static size of the grid starting at 3x3.
     */
    static int grid_size;

    /**
     * @brief Number of games to be played in a session
     */
    int number_of_games = 1;

    /**
     * @brief The game board represented by a 2D character array.
     * * Initialized with empty spaces ' '.
     */
    vector<vector<char>> Board;

    /**
     * @brief The current player's symbol ('X' or 'O').
     * * Initialized to 'X'.
     */
    char current_player = 'X';

    /**
     * @brief The difficulty level of the AI.
     * * Values:
     * - 1: Easy (Random moves)
     * - 2: Medium (Defensive/Balanced)
     * - 3: Hard (Minimax/Optimal)
     */
    int difficulty;

public:
    /**
     * @brief Constructor for the TicTacToe class.
     * * Initializes the game with the selected difficulty.
     * @param difficulty Integer representing the difficulty level (1, 2, or 3).
     */
    TicTacToe(int difficulty, int number_of_games);

    /**
     * @brief Retrieves the size of the game grid.
     */
    int getGridSize() const;

    /**
     * @brief Retrieves the content of a specific cell on the board.
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @return char The character in the specified cell ('X', 'O', or '_').
     */
    char getCell(int row, int col) const;

    /**
     * @brief Displays the current game board to the console.
     * * This function formats and prints the 3x3 grid.
     */
    void displayBoard();

    /**
     * @brief Resets the game board to play a new game.
     * * This function formats and prints the grid.
     */
    void Board_Reset();

    /**
     * @brief Retrieves a list of all empty cells on the board.
     * * @return std::vector<std::pair<int, int>> A vector of pairs (row, col) representing available moves.
     */
    vector<pair<int, int>> getEmptyCells();

    /**
     * @brief Calculates the computer's next move based on the difficulty level.
     * * @return std::pair<int, int> The coordinates (row, col) selected by the computer.
     */
    pair<int, int> getComputerMove();

    /**
     * @brief Prompts the human player to choose a position on the board.
     * * Validates input to ensure the chosen cell is empty and within bounds.
     * @return pair<int, int> The coordinates (row, col) chosen by the player.
     */
    pair<int, int> ChosePosition();

    /**
     * @brief Plays a move for the current player at the specified position.
     * @param row The row index where the player wants to place their symbol.
     * @param col The column index where the player wants to place their symbol.
     * @return true If the move was successful (cell was empty).
     * @return false If the move was invalid (cell already occupied).
     */
    bool playMove(int row, int col);

    /**
     * @brief Switches the current player.
     * * Toggles the 'current_player' attribute between 'X' and 'O'.
     */
    void Switchplayer();

    /**
     * @brief Checks if the last move resulted in a win.
     * * @param row The row index of the last move.
     * @param col The column index of the last move.
     * @param current_player The symbol of the player who made the last move.
     * @return true If the move created a winning line.
     * @return false Otherwise.
     */
    bool Win(int row, int col, char current_player);

    /**
     * @brief Checks if the game is a tie (draw).
     * * A tie occurs if the board is full and no player has won.
     * @return true If the game is a tie.
     * @return false If moves are still available.
     */
    bool Tie();

    /**
     * @brief Manages a session of multiple games.
     * * Loops through the specified number of games, resetting the board each time.
     * @param number_of_games The total number of games to be played in the session.
     */
    void Session(int number_of_games);

    /**
     * @brief Executes a single turn of the game logic.
     * * Handles input for the human player or triggers the computer move,
     * then updates the board state.
     * @return std::pair<bool, int> A pair where the first element indicates if the game continues,
     * and the second element indicates the game status (win/tie/lose).
     */
    pair<bool, int> Play();
};

#endif
