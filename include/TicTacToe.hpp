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
     * @brief Static size of the grid (3x3).
     */
    static const int grid_size = 5;

    /**
     * @brief Number of games to be played in a session
     */
    int number_of_games;

    /**
     * @brief The game board represented by a 2D character array.
     * * Initialized with empty spaces ' '.
     */
    char Board[grid_size][grid_size];

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
     * @brief Displays the current game board to the console.
     * * This function formats and prints the 3x3 grid.
     */
    void displayBoard();

    /**
     * @brief Resets the game board to play a new game.
     * * This function formats and prints the 3x3 grid.
     */
    void Board_Reset();

    /**
     * @brief Retrieves a list of all empty cells on the board.
     * * @return std::vector<std::pair<int, int>> A vector of pairs (row, col) representing available moves.
     */
    std::vector<std::pair<int, int>> getEmptyCells();

    /**
     * @brief Calculates the computer's next move based on the difficulty level.
     * * @return std::pair<int, int> The coordinates (row, col) selected by the computer.
     */
    std::pair<int, int> getComputerMove();

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
     * * Resets the board and alternates starting players for each game.
     * @param number_of_games The total number of games to be played in the session.
     */
    void Session(int number_of_games);

    /**
     * @brief Executes a single turn of the game logic.
     * * Handles input for the human player or triggers the computer move,
     * then updates the board state.
     * @return true If the move was valid and the game continues.
     * @return false If the game has ended or an error occurred.
     */
    bool Play();
};

#endif
