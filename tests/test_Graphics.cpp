/**
 * @file test_Graphics.cpp
 * @brief Unit tests for Graphics class using Catch2
 */

#include <catch2/catch_test_macros.hpp>
#include "Graphics.hpp"
#include "TicTacToe.hpp"
#include <SFML/Graphics.hpp>

TEST_CASE("Player move handling", "[player][move]")
{
    SECTION("Valid player move")
    {
        TicTacToe game(0, 1);
        Graphics graphics(game);

        graphics.handlePlayerMove(0, 0);
        REQUIRE(game.getCell(0, 0) == 'X');
    }

    SECTION("Invalid move on occupied cell")
    {
        TicTacToe game(0, 1);
        Graphics graphics(game);

        graphics.handlePlayerMove(0, 0);
        REQUIRE(game.getCell(0, 0) == 'X');

        // Try to play the same cell
        graphics.handlePlayerMove(0, 0);
        REQUIRE(game.getCell(0, 0) == 'X');
    }
}

TEST_CASE("Win detection and handling", "[win]")
{
    SECTION("Player X wins horizontal")
    {
        TicTacToe game(0, 1);
        Graphics graphics(game);

        graphics.handlePlayerMove(0, 0); // X
        game.Switchplayer();
        graphics.handlePlayerMove(1, 0); // O
        game.Switchplayer();
        graphics.handlePlayerMove(0, 1); // X
        game.Switchplayer();
        graphics.handlePlayerMove(1, 1); // O
        game.Switchplayer();
        graphics.handlePlayerMove(0, 2); // X wins

        // Game should be over
        REQUIRE(game.Win(0, 2, 'X') == true);
    }

    SECTION("Computer wins")
    {
        TicTacToe game(1, 1);
        Graphics graphics(game);

        // Simulate computer win
        game.setCurrentPlayer('O');
        game.playMove(0, 0);
        game.playMove(0, 1);
        game.playMove(0, 2);

        REQUIRE(game.Win(0, 2, 'O') == true);
    }
}

TEST_CASE("Tie detection and handling", "[tie]")
{
    TicTacToe game(0, 1);
    Graphics graphics(game);

    // Create a tie
    // X O X
    // X O O
    // O X X
    graphics.handlePlayerMove(0, 0); // X
    game.Switchplayer();
    graphics.handlePlayerMove(0, 1); // O
    game.Switchplayer();
    graphics.handlePlayerMove(0, 2); // X
    game.Switchplayer();
    graphics.handlePlayerMove(1, 1); // O
    game.Switchplayer();
    graphics.handlePlayerMove(1, 0); // X
    game.Switchplayer();
    graphics.handlePlayerMove(1, 2); // O
    game.Switchplayer();
    graphics.handlePlayerMove(2, 1); // X
    game.Switchplayer();
    graphics.handlePlayerMove(2, 0); // O
    game.Switchplayer();
    graphics.handlePlayerMove(2, 2); // X

    REQUIRE(game.Tie() == true);
}

TEST_CASE("Grid size increases after win", "[gridSize ++]")
{
    TicTacToe game(0, 3);
    Graphics graphics(game);

    int initialSize = game.getGridSize();

    // Simulate win
    graphics.handlePlayerWin('X');
    graphics.handleNextGame();

    if (initialSize < 6)
    {
        REQUIRE(game.getGridSize() == initialSize + 1);
    }
}

TEST_CASE("Grid size resets to 3 after loss", "[gridSize 3]")
{
    TicTacToe game(1, 3);
    Graphics graphics(game);

    game.setGridSize(5);
    game.Board_Reset();

    // Simulate loss against computer
    graphics.handlePlayerWin('O');
    graphics.handleNextGame();

    REQUIRE(game.getGridSize() == 3);
}

TEST_CASE("Grid size stays same after tie", "[gridSize=]")
{
    TicTacToe game(0, 3);
    Graphics graphics(game);

    game.setGridSize(4);
    game.Board_Reset();
    int sizeBefore = game.getGridSize();

    graphics.handleTie();
    graphics.handleNextGame();

    REQUIRE(game.getGridSize() == sizeBefore);
}