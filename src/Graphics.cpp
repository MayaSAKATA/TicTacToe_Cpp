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

#include <thread> // for delay
#include <chrono>

using namespace std;
using namespace sf;

Graphics::Graphics(TicTacToe &game) : game(game), gameOver(false), lastGameResult(0), gamesPlayed(0)
{
    maxGames = game.getNumberOfGames();
    updateWindowSize();
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

void Graphics::updateWindowSize()
{
    int gridSize = game.getGridSize();
    if (window.isOpen())
    {
        window.close();
    }
    window.create(VideoMode({(unsigned int)(gridSize * CELL_SIZE), (unsigned int)(gridSize * CELL_SIZE)}), "Tic Tac Toe");
    window.setFramerateLimit(60);
}

void Graphics::handleNextGame()
{
    int gridSize = game.getGridSize();
    // Ajust grid size based on last game result
    switch (lastGameResult)
    {
    case 1: // Win - increase grid size
        if (gridSize < 6)
        {
            game.setGridSize(gridSize++);
            updateWindowSize();
        }
        break;
    case 3: // Lose - set grid to 3x3
        game.setGridSize(3);
        updateWindowSize();
        break;
    case 2: // Tie - same grid size
        break;
    }

    // Reset game state
    game.Board_Reset();
    game.setCurrentPlayer('X');
    gameOver = false;
    lastGameResult = 0;

    cout << "\nStarting next game... (Grid size: " << game.getGridSize() << "x" << game.getGridSize() << ")\n"
         << endl;
    cout << "\nGame " << gamesPlayed + 1 << " / " << maxGames << "\n"
         << endl;
}

void Graphics::processEvents()
{
    int gridSize = game.getGridSize();

    while (const auto event = window.pollEvent())
    {
        if (event->is<Event::Closed>())
        {
            window.close();
        }
        else if (const auto *key = event->getIf<Event::KeyPressed>())
        {
            if (gameOver)
            {
                if (key->code == Keyboard::Key::Space)
                {
                    // Check if more games are allowed
                    if (gamesPlayed < maxGames)
                    {
                        handleNextGame();
                    }
                    else
                    {
                        cout << "\nSession over! All " << maxGames << " games completed." << endl;
                        cout << "Thanks for playing!" << endl;
                        window.close();
                    }
                }
                else if (key->code == Keyboard::Key::Escape)
                {
                    cout << "Thanks for playing! Games completed: " << gamesPlayed << " / " << maxGames << endl;
                    window.close();
                }
            }
        }
        else if (const auto *mouseButton = event->getIf<Event::MouseButtonPressed>())
        {
            if (!gameOver && mouseButton->button == Mouse::Button::Left)
            {
                int col = mouseButton->position.x / CELL_SIZE;
                int row = mouseButton->position.y / CELL_SIZE;

                if (row >= 0 && row < gridSize && col >= 0 && col < gridSize)
                {
                    // Save current player
                    char currentPlayer = game.getCurrentPlayer();

                    // Try to play the move
                    if (game.playMove(row, col))
                    {
                        cout << "Player '" << currentPlayer << "' plays (" << row << "," << col << ")" << endl;

                        // Check for win
                        if (game.Win(row, col, currentPlayer))
                        {
                            if (game.getDifficulty() > 0 && currentPlayer == 'O')
                            {
                                cout << "\nCOMPUTER WINS!" << endl;
                                lastGameResult = 3;
                            }
                            else
                            {
                                cout << "\nPLAYER '" << currentPlayer << "' WINS!" << endl;
                                lastGameResult = 1;
                            }
                            gameOver = true;
                            gamesPlayed++;
                            return;
                        }

                        // Check for tie
                        if (game.Tie())
                        {
                            cout << "\nIT'S A TIE!" << endl;
                            lastGameResult = 2;
                            gameOver = true;
                            gamesPlayed++;
                            return;
                        }

                        // Change player
                        game.Switchplayer();

                        // If it is the computer's turn
                        if (game.getDifficulty() > 0 && game.getCurrentPlayer() == 'O')
                        {
                            pair<int, int> computerMove = game.getComputerMove();
                            int compRow = computerMove.first;
                            int compCol = computerMove.second;

                            if (game.playMove(compRow, compCol))
                            {
                                cout << "Computer plays (" << compRow << "," << compCol << ")" << endl;

                                if (game.Win(compRow, compCol, game.getCurrentPlayer()))
                                {
                                    cout << "\nCOMPUTER WINS!" << endl;
                                    lastGameResult = 3;
                                    gameOver = true;
                                    gamesPlayed++;
                                    return;
                                }

                                if (game.Tie())
                                {
                                    cout << "\nIT'S A TIE!" << endl;
                                    lastGameResult = 2;
                                    gameOver = true;
                                    gamesPlayed++;
                                    return;
                                }

                                game.Switchplayer();
                            }
                        }
                    }
                    else
                    {
                        cout << "\nCell already occupied!" << endl;
                    }
                }
            }
        }
    }
}

void Graphics::run()
{
    cout << "Starting session: " << maxGames << " game(s)" << endl;
    cout << "\nGame " << gamesPlayed + 1 << " / " << maxGames << "\n"
         << endl;

    while (window.isOpen())
    {
        processEvents();

        window.clear(Color::White);
        drawGrid();
        drawPieces();

        window.display();
    }
}