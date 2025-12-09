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
    float radius = CELL_SIZE * 0.3f; // 30% of the size of the cell
    CircleShape circle(radius);
    circle.setFillColor(Color::Transparent);       // Empty fill
    circle.setOutlineThickness(CELL_SIZE * 0.05f); // 5% of the size of the cell
    circle.setOutlineColor(Color::Blue);
    circle.setOrigin({radius, radius}); // Center of the circle (radius, radius)

    // Positioning the circle at the center of the cell
    float centerX = col * CELL_SIZE + CELL_SIZE / 2.f;
    float centerY = row * CELL_SIZE + CELL_SIZE / 2.f;

    circle.setPosition({centerX, centerY});
    window.draw(circle);
}

void Graphics::drawCross(int col, int row)
{
    // Red cross
    float lineLength = CELL_SIZE * 0.7f;     // 70% of the size of the cell
    float lineThickness = CELL_SIZE * 0.05f; // 5% of the size of the cell

    RectangleShape line1({lineLength, lineThickness}); // First line of the cross
    line1.setFillColor(Color::Red);
    line1.setOrigin({lineLength / 2.f, lineThickness / 2.f});
    line1.setRotation(degrees(45.f));

    RectangleShape line2({lineLength, lineThickness}); // Second line of the cross
    line2.setFillColor(Color::Red);
    line2.setOrigin({lineLength / 2.f, lineThickness / 2.f});
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
    window.setPosition({900, 100});
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
            gridSize++;
            game.setGridSize(gridSize);
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

void Graphics::handleSpaceKey()
{
    if (gamesPlayed < maxGames)
    {
        handleNextGame();
    }
    else
    {
        if (maxGames == 1)
        {

            cout << "\nGame over!\n"
                 << endl;
        }
        else
        {
            cout << "\nSession over! All " << maxGames << " games completed." << endl;
        }
        cout << "Thanks for playing!\n"
             << endl;
        window.close();
    }
}

void Graphics::handleEscapeKey()
{
    cout << "\nThanks for playing! Games completed: " << gamesPlayed << " / " << maxGames << "\n"
         << endl;
    window.close();
}

void Graphics::handleKeyPressed(const Event::KeyPressed *key)
{
    if (!gameOver)
        return; // Only process keys if the game is over

    if (key->code == Keyboard::Key::Space)
    {
        handleSpaceKey();
    }
    else if (key->code == Keyboard::Key::Escape)
    {
        handleEscapeKey();
    }
}

void Graphics::handleMousePressed(const Event::MouseButtonPressed *mouseButton)
{
    if (gameOver || mouseButton->button != Mouse::Button::Left)
        return;

    int gridSize = game.getGridSize();
    int col = mouseButton->position.x / CELL_SIZE;
    int row = mouseButton->position.y / CELL_SIZE;

    // Vérifier que le clic est dans la grille
    if (row < 0 || row >= gridSize || col < 0 || col >= gridSize)
        return;

    handlePlayerMove(row, col);
}

void Graphics::handlePlayerMove(int row, int col)
{
    char currentPlayer = game.getCurrentPlayer();

    if (!game.playMove(row, col))
    {
        cout << "\nCell already occupied!" << endl;
        return;
    }

    cout << "Player '" << currentPlayer << "' plays (" << row << "," << col << ")" << endl;

    // Vérifier victoire
    if (game.Win(row, col, currentPlayer))
    {
        handlePlayerWin(currentPlayer);
        return;
    }

    // Vérifier égalité
    if (game.Tie())
    {
        handleTie();
        return;
    }

    // Changer de joueur et gérer le tour de l'ordinateur si nécessaire
    game.Switchplayer();

    if (game.getDifficulty() > 0 && game.getCurrentPlayer() == 'O')
    {
        handleComputerMove();
    }
}

void Graphics::handlePlayerWin(char player)
{
    if (game.getDifficulty() > 0 && player == 'O')
    {
        cout << "\nCOMPUTER WINS!" << endl;
        lastGameResult = 3;
    }
    else
    {
        cout << "\nPLAYER '" << player << "' WINS!" << endl;
        lastGameResult = 1;
    }

    cout << "\nPress SPACE to play next round, ESC to quit the game\n"
         << endl;
    gameOver = true;
    gamesPlayed++;
}

void Graphics::handleTie()
{
    cout << "\nIT'S A TIE!" << endl;
    cout << "\nPress SPACE to play next round, ESC to quit the game\n"
         << endl;
    lastGameResult = 2;
    gameOver = true;
    gamesPlayed++;
}

void Graphics::handleComputerMove()
{
    pair<int, int> computerMove = game.getComputerMove();
    int compRow = computerMove.first;
    int compCol = computerMove.second;

    if (!game.playMove(compRow, compCol))
        return;

    cout << "Computer plays (" << compRow << "," << compCol << ")" << endl;

    // Vérifier victoire de l'ordinateur
    if (game.Win(compRow, compCol, game.getCurrentPlayer()))
    {
        cout << "\nCOMPUTER WINS!" << endl;
        cout << "\nPress SPACE to play next round, ESC to quit the game\n"
             << endl;
        lastGameResult = 3;
        gameOver = true;
        gamesPlayed++;
        return;
    }

    // Vérifier égalité
    if (game.Tie())
    {
        cout << "\nIT'S A TIE!" << endl;
        cout << "\nPress SPACE to play next round, ESC to quit the game\n"
             << endl;
        lastGameResult = 2;
        gameOver = true;
        gamesPlayed++;
        return;
    }

    game.Switchplayer();
}

void Graphics::processEvents()
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<Event::Closed>())
        {
            window.close();
        }
        else if (const auto *key = event->getIf<Event::KeyPressed>())
        {
            handleKeyPressed(key);
        }
        else if (const auto *mouseButton = event->getIf<Event::MouseButtonPressed>())
        {
            handleMousePressed(mouseButton);
        }
    }
}

void Graphics::run()
{
    if (maxGames < 1)
    {
        cout << "Starting session: " << maxGames << " games" << endl;
        cout << "\nGame " << gamesPlayed + 1 << " / " << maxGames << "\n"
             << endl;
    }

    while (window.isOpen())
    {
        processEvents();

        window.clear(Color::White);
        drawGrid();
        drawPieces();

        window.display();
    }
}