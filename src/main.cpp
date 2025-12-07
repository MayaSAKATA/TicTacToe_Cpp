/**
 * @file main.cpp
 * @brief Entry point for the TicTacToe game application.
 * @details Handles user interaction for game setup and starts the game session.
 */

#include "TicTacToe.hpp"
#include "Graphics.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#include <thread> // for delay
#include <chrono>

using namespace std;
using namespace sf;

int main()
{
    int players, level, number_of_games;
    cout << "\nWelcome to Tic Tac Toe!\n";
    cout << "\n======================\n";

    cout << "How many players?\n1. Two Players (Human vs Human)\n2. One Player (vs Computer)\n\nEnter your choice (1-2): ";
    cin >> players;
    while (players < 1 || players > 2)
    {
        cout << "Only two options available 1 or 2" << endl;
        cin >> players;
    }
    if (players == 2)
    {
        cout << "\nSelect difficulty level:\n1. Easy\n2. Hard (not implemented)\n\nEnter your choice (1-2): ";
        cin >> level;
        while (level < 1 || level > 2)
        {
            cout << "Only two levels available 1 or 2" << endl;
            cin >> level;
        }
    }
    else
    {
        level = 0; // Two players mode
    }
    cout << "\nHow many games in row? ";
    cin >> number_of_games;

    cout << "\nLet's play! Opening game window...\n";
    this_thread::sleep_for(chrono::seconds(1)); // 2 seconds delay

    //     Game.Session(number_of_games);

    TicTacToe game(level, number_of_games);
    Graphics graphics(game);
    graphics.run();

    return 0;
}