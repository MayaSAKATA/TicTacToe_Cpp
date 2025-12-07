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
    int gridSize = game.getGridSize();

    window.create(VideoMode({(unsigned int)(gridSize * CELL_SIZE), (unsigned int)(gridSize * CELL_SIZE)}), "Tic Tac Toe");
    window.setFramerateLimit(60);
}

void Graphics::drawCircle(int col, int row)
{
    // Blue circle
    CircleShape circle(60.f);                // Radius 60px
    circle.setFillColor(Color::Transparent); // Empty fill
    circle.setOutlineThickness(10.f);        // Outline thickness
    circle.setOutlineColor(Color::Blue);
    circle.setOrigin({60.f, 60.f}); // Center of the circle (radius, radius)

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
    int gridSize = game.getGridSize();
    // Vertical lines
    for (int i = 1; i < gridSize; i++)
    {
        RectangleShape line(Vector2f(5, CELL_SIZE * gridSize));
        line.setPosition(Vector2f(i * CELL_SIZE, 0));
        line.setFillColor(gridColor);
        window.draw(line);
    }

    // Horizontal lines
    for (int i = 1; i < gridSize; i++)
    {
        RectangleShape line(Vector2f(CELL_SIZE * gridSize, 5));
        line.setPosition(Vector2f(0, i * CELL_SIZE));
        line.setFillColor(gridColor);
        window.draw(line);
    }
}

void Graphics::drawPieces()
{
    int gridSize = game.getGridSize();

    for (int row = 0; row < gridSize; row++)
    {
        for (int col = 0; col < gridSize; col++)
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
    int gridSize = game.getGridSize();
    char current_player = game.getCurrentPlayer();

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
                // Conversion pixels -> grid coordinates
                int col = mouseButton->position.x / CELL_SIZE;
                int row = mouseButton->position.y / CELL_SIZE;

                if (game.playMove(row, col))
                {
                    cout << "Click on " << row << "," << col << endl;

                    // Check for win
                    if (game.Win(row, col, current_player))
                    {
                        cout << "PLAYER '" << current_player << "' WINS!" << endl;
                        // Draw final state
                        window.clear(Color::White);
                        drawGrid();
                        drawPieces();
                        window.display();

                        // Wait before closing
                        sf::sleep(sf::seconds(2));
                        window.close();
                        return;
                    }
                    // Check for tie
                    if (game.Tie())
                    {
                        cout << "It's a TIE!" << endl;
                        window.clear(Color::White);
                        drawGrid();
                        drawPieces();
                        window.display();

                        sf::sleep(sf::seconds(2));
                        window.close();
                        return;
                    }
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