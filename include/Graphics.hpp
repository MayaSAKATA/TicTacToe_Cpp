/**
 * @file Graphics.hpp
 * @brief Header file defining the Game class
 * @author Florient SAKIYE, Maya SAKATA
 * @date 2025
 */

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include "TicTacToe.hpp"

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
using namespace sf;

/**
 * @class Graphics
 * @brief Class responsible for rendering the TicTacToe game using SFML.
 * * Manages the game window, drawing the grid and pieces, and handling user input.
 */
class Graphics
{
private:
    /**
     * @brief SFML RenderWindow for displaying the game.
     */
    RenderWindow window;
    /**
     * @brief Reference to the TicTacToe game logic.
     */
    TicTacToe &game;

    /**
     * @brief Game over status. True : game ended, False : game ongoing.
     */
    bool gameOver;
    /**
     * @brief Result of the last game played:  1: win, 2: tie, 3: lose
     */
    int lastGameResult;
    /**
     * @brief Maximum number of games in the session
     */
    int maxGames;
    /**
     * @brief Number of games played so far
     */
    int gamesPlayed;

    /**
     * @brief Size of each cell in pixels
     */
    const unsigned int CELL_SIZE = 100; // Hardcoded size of each cell in pixels

public:
    // DRAWING METHODS

    /**
     * @brief Draw the TicTacToe grid on the window.
     */
    void drawGrid();
    /**
     * @brief Draw all the pieces on the board.
     */
    void drawPieces();
    /**
     * @brief Draw a circle ('O') at the specified grid position.
     * @param col Column index
     * @param row Row index
     */
    void drawCircle(int col, int row);
    /**
     * @brief Draw a cross ('X') at the specified grid position.
     * @param col Column index
     * @param row Row index
     */
    void drawCross(int col, int row);

    /**
     * @brief Update the window size based on the current grid size.
     */
    void updateWindowSize();

    // HANDLERS

    /**
     * @brief Handle the transition to the next game in the session.
     */
    void handleNextGame();
    /**
     * @brief Handle the keyboard events.
     * @param key Pointer to the KeyPressed event data.
     */
    void handleKeyPressed(const Event::KeyPressed *key);
    /**
     * @brief Handle space key actions.
     */
    void handleSpaceKey();
    /**
     * @brief Handle escape key actions.
     */
    void handleEscapeKey();
    /**
     * @brief Handle mouse button pressed events.
     * @param mouseButton Pointer to the MouseButtonPressed event data.
     */
    void handleMousePressed(const Event::MouseButtonPressed *mouseButton);
    /**
     * @brief Handle a player's move at the specified grid position.
     * @param row Row index
     * @param col Column index
     */
    void handlePlayerMove(int row, int col);
    /**
     * @brief Handle actions when a player wins.
     * @param player The symbol of the winning player ('X' or 'O').
     */
    void handlePlayerWin(char player);
    /**
     * @brief Handle actions when the game ends in a tie.
     */
    void handleTie();
    /**
     * @brief Handle the computer player's move.
     */
    void handleComputerMove();
    /**
     * @brief Process SFML window events (input, closing, etc.).
     */
    void processEvents();

    /**
     * @brief Constructor for the Graphics class.
     * @param game Reference to the TicTacToe game logic.
     */
    Graphics(TicTacToe &game);
    /**
     * @brief Main loop to run the graphical game.
     */
    void run();
};

#endif