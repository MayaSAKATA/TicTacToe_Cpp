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
 */
class Graphics
{
private:
    RenderWindow window;
    TicTacToe &game;

    const unsigned int CELL_SIZE = 200; // Size of each cell in pixels
    const unsigned int GRID_SIZE = 3;

    void drawGrid();
    void drawPieces();
    void processEvents();
    void drawCircle(int colonne, int ligne);
    void drawCross(int colonne, int ligne);

public:
    Graphics(TicTacToe &game);
    void run();
};

#endif