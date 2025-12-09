/**
 * @file test_TicTacToe.cpp
 * @brief Unit tests for TicTacToe class using Catch2
 */

#include <catch2/catch_test_macros.hpp>

#include "../include/TicTacToe.hpp"

TEST_CASE("Constructor initializes game correctly", "[constructor]")
{
    TicTacToe game(1, 3);

    REQUIRE(game.getGridSize() == 3);
    REQUIRE(game.getCurrentPlayer() == 'X');
    REQUIRE(game.getDifficulty() == 1);
    REQUIRE(game.getNumberOfGames() == 3);
}

TEST_CASE("Board is initialized with empty cells", "[board][init]")
{
    TicTacToe game(0, 1);

    for (int i = 0; i < game.getGridSize(); i++)
    {
        for (int j = 0; j < game.getGridSize(); j++)
        {
            REQUIRE(game.getCell(i, j) == '_');
        }
    }
}

TEST_CASE("Player switching works correctly", "[player]")
{
    TicTacToe game(0, 1);

    REQUIRE(game.getCurrentPlayer() == 'X');

    game.Switchplayer();
    REQUIRE(game.getCurrentPlayer() == 'O');

    game.Switchplayer();
    REQUIRE(game.getCurrentPlayer() == 'X');
}

TEST_CASE("Computer only chooses empty cells")
{
    TicTacToe game(0, 1);

    // Almost fill the grid
    game.playMove(0, 0);
    game.playMove(0, 1);
    game.playMove(0, 2);
    game.playMove(1, 0);
    game.playMove(1, 1);
    game.playMove(1, 2);
    game.playMove(2, 0);
    game.playMove(2, 1);
    // (2,2) is empty

    auto move = game.getComputerMove();
    REQUIRE(move.first == 2);
    REQUIRE(move.second == 2);
}

TEST_CASE("Win detection on different grid sizes", "[win][grid]")
{
    SECTION("4x4 grid horizontal win")
    {
        TicTacToe game(0, 1);
        game.setGridSize(4);
        game.Board_Reset();

        game.playMove(0, 0);
        game.playMove(0, 1);
        game.playMove(0, 2);
        game.playMove(0, 3);

        REQUIRE(game.Win(0, 3, 'X') == true);
    }

    SECTION("5x5 grid diagonal win")
    {
        TicTacToe game(0, 1);
        game.setGridSize(5);
        game.Board_Reset();

        game.playMove(0, 0);
        game.playMove(1, 1);
        game.playMove(2, 2);
        game.playMove(3, 3);
        game.playMove(4, 4);

        REQUIRE(game.Win(4, 4, 'X') == true);
    }
}