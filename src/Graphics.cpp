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

void Graphics::drawCircle(int col, int row)
{
    // Blue circle
    CircleShape circle(70.f);                    // Radius 70px
    circle.setFillColor(sf::Color::Transparent); // Empty fill
    circle.setOutlineThickness(10.f);            // Outline thickness
    circle.setOutlineColor(sf::Color::Blue);

    // Positioning the circle in the cell
    float posX = col * 200.f + 30.f;
    float posY = row * 200.f + 30.f;

    circle.setPosition({posX, posY});
    window.draw(circle);
}

void Graphics::drawCross(int col, int row)
{
    // Red cross
    RectangleShape line1(Vector2f(140.f, 10.f)); // First line of the cross
    line1.setFillColor(sf::Color::Red);
    line1.setRotation(degrees(45.f));

    RectangleShape line2(Vector2f(140.f, 10.f)); // Second line of the cross
    line2.setFillColor(sf::Color::Red);
    line2.setRotation(degrees(-45.f));

    // Positioning the cross in the cell
    float posX = col * 200.f + 30.f;
    float posY = row * 200.f + 30.f;

    line1.setPosition({posX, posY + 70.f});
    line2.setPosition({posX, posY + 70.f});

    window.draw(line1);
    window.draw(line2);
}

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
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            char cell = game.getCell(row, col);
            if (cell == 'O')
            {
                drawCircle(col, row);
            }
            else if (cell == 'X')
            {
                drawCross(col, row);
            }
        }
    }
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