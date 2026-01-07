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
    string input;

    cout << "\nWelcome to Tic Tac Toe!\n";
    cout << "\n======================\n";
    cout << "\nHow many players?\n1. Two Players (Human vs Human)\n2. One Player (vs Computer)\n\nEnter your choice (1-2): ";

    while (true)
    {
        cin >> input;
        if (input == "1" || input == "2")
        {
            players = stoi(input);
            break;
        }
        else
        {
            cout << "Only two options available 1 or 2\nPlease retry:" << endl;
        }
    }
    if (players == 2)
    {
        cout << "\nSelect difficulty level:\n1. Easy\n2. Hard\n\nEnter your choice (1-2): ";
        while (true)
        {
            cin >> input;
            if (input == "1" || input == "2")
            {
                level = stoi(input);
                break;
            }
            else
            {
                cout << "Only two levels available 1 or 2\nPlease retry:" << endl;
            }
        }
    }
    else
    {
        level = 0; // 2 players mode (human vs human), no difficulty
    }
    cout << "\nHow many games in a row? ";
    while (true)
    {
        cin >> input;
        try
        {
            number_of_games = stoi(input);
            if (number_of_games > 0)
            {
                break;
            }
            cout << "Please enter a number greater than 0\nPlease retry: ";
        }
        catch (...) // catch all expections
        {
            cout << "\nPlease retry: ";
        }
    }

    cout << "\nLet's play! Opening game window...\n\n";
    this_thread::sleep_for(chrono::seconds(1)); // 2 seconds delay

    TicTacToe game(level, number_of_games);

    // Play in console mode
    game.Session(number_of_games);

    // Play in graphical mode
    // Graphics graphics(game);
    // graphics.run();

    return 0;
}