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
    CircleShape circle(60.f);                // Radius 60px
    circle.setFillColor(Color::Transparent); // Empty fill
    circle.setOutlineThickness(10.f);        // Outline thickness
    circle.setOutlineColor(Color::Blue);
    circle.setOrigin({60.f, 60.f}); // Centre du cercle (rayon, rayon)

    // Positioning the circle at the center of the cell
    float centerX = col * CELL_SIZE + CELL_SIZE / 2.f;
    float centerY = row * CELL_SIZE + CELL_SIZE / 2.f;

    circle.setPosition({centerX, centerY});
    window.draw(circle);
}

void Graphics::drawCross(int col, int row)
{
    // Red cross
    RectangleShape line1({140.f, 10.f}); // First line of the cross
    line1.setFillColor(Color::Red);
    line1.setOrigin({70.f, 5.f});
    line1.setRotation(degrees(45.f));

    RectangleShape line2({140.f, 10.f}); // Second line of the cross
    line2.setFillColor(Color::Red);
    line2.setOrigin({70.f, 5.f});
    line2.setRotation(degrees(-45.f));

    // Positioning the cross at the center of the cell
    float centerX = col * CELL_SIZE + CELL_SIZE / 2.f;
    float centerY = row * CELL_SIZE + CELL_SIZE / 2.f;

    line1.setPosition({centerX, centerY});
    line2.setPosition({centerX, centerY});

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
    while (const auto event = window.pollEvent())
    {
        if (event->is<Event::Closed>())
        {
            window.close();
        }
        else if (const auto *mouseButton = event->getIf<Event::MouseButtonPressed>())
        {
            if (mouseButton->button == Mouse::Button::Left)
            {
                // Conversion pixels -> case du tableau
                int col = mouseButton->position.x / CELL_SIZE;
                int row = mouseButton->position.y / CELL_SIZE;

                if (game.playMove(row, col))
                {
                    cout << "Click on " << row << "," << col << endl;

                    // check for win or draw here if needed
                    game.Switchplayer();
                }
            }
        }
    }
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