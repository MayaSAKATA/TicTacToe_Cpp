/**
 * @file Graphics.cpp
 * @brief Implementation of the Graphics class methods.
 * @details Contains the logic for board rendering, move validation,
 * computer moves algorithms, and game loop management.
 */

#include "Graphics.hpp"
#include "TicTacToe.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

Graphics::Graphics(TicTacToe &game) : game(game)
{
    window.create(VideoMode({(unsigned int)(GRID_SIZE * CELL_SIZE), (unsigned int)(GRID_SIZE * CELL_SIZE)}), "Tic Tac Toe");
    window.setFramerateLimit(60);
}

void Graphics::drawCircle(int colonne, int ligne)
{
}

void Graphics::drawCross(int colonne, int ligne) {}

void Graphics::drawGrid()
{
    Color gridColor = Color::Black;

    // Vertical lines
    for (int i = 1; i < GRID_SIZE; i++)
    {
        RectangleShape line(Vector2f(5, CELL_SIZE * GRID_SIZE));
        line.setPosition(Vector2f(i * CELL_SIZE, 0));
        line.setFillColor(gridColor);
        window.draw(line);
    }

    // Horizontal lines
    for (int i = 1; i < GRID_SIZE; i++)
    {
        RectangleShape line(Vector2f(CELL_SIZE * GRID_SIZE, 5));
        line.setPosition(Vector2f(0, i * CELL_SIZE));
        line.setFillColor(gridColor);
        window.draw(line);
    }
}

void Graphics::drawPieces()
{
}

void Graphics::processEvents()
{
}

void Graphics::run()
{
    while (window.isOpen())
    {
        processEvents();

        window.clear(Color::White);

        drawGrid();
        drawPieces();

        window.display();
    }
}