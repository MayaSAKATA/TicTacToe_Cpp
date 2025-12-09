/**
 * @file TicTacToe.cpp
 * @brief Implementation of the TicTacToe class methods.
 * @details Contains the logic for board rendering, move validation,
 * computer moves algorithms, and game loop management.
 */

#include "TicTacToe.hpp"

int TicTacToe::grid_size = 3;

using namespace std;

TicTacToe::TicTacToe(int level, int games)
{
    current_player = 'X';
    difficulty = level; // Computer move difficulty : 1. easy, 2. hard
    number_of_games = games;
    srand(time(0));

    grid_size = 3; // Initial grid size starting at 3x3

    Board.resize(grid_size, std::vector<char>(grid_size)); // Resize the board to grid_size x grid_size

    // Initialize the board with empty positions
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++)
            Board[i][j] = '_';
}

int TicTacToe::getGridSize() const
{
    return grid_size;
}

char TicTacToe::getCell(int row, int col) const
{
    if (row >= 0 && row < grid_size && col >= 0 && col < grid_size)
    {
        return Board[row][col];
    }
    return '_';
}

char TicTacToe::getCurrentPlayer() const
{
    return current_player;
}

int TicTacToe::getDifficulty()
{
    return difficulty;
}

int TicTacToe::getNumberOfGames() const
{
    return number_of_games;
}

void TicTacToe::setGridSize(int size)
{
    grid_size = size;
}

void TicTacToe::setCurrentPlayer(char player)
{
    current_player = player;
}

void TicTacToe::displayBoard()
{
    int num = 1; // empty cell numbering starts from 1
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            string cell;
            // Displays the cell content or its number if empty
            if (Board[i][j] == '_')
            {
                if (num < 10)
                {
                    cell = " " + to_string(num);
                }
                else
                {
                    cell = to_string(num);
                }
            }
            else
            {
                cell = " " + string(1, Board[i][j]);
            }
            cout << " " << cell << " ";
            if (j < grid_size - 1)
            {
                cout << "|";
            }
            num++;
        }
        cout << endl;
        for (int j = 0; j < grid_size; j++)
        {
            if (j != grid_size - 1)
            {

                cout << "----+";
            }
            else
            {
                cout << "----";
            }
        }
        cout << endl;
    }
    cout << '\n';
}

void TicTacToe::Board_Reset()
{
    Board.resize(grid_size); // Resize the number of rows
    for (int i = 0; i < grid_size; i++)
    {
        Board[i].resize(grid_size); // Resize each row to have grid_size columns
        for (int j = 0; j < grid_size; j++)
        {
            Board[i][j] = '_'; // Reset each cell to empty
        }
    }
}

void TicTacToe::Switchplayer()
{
    if (current_player == 'X')
        current_player = 'O'; // Switch from X to O
    else
        current_player = 'X'; // Switch from O to X
}

bool TicTacToe::Win(int row, int col, char current_player)
{
    // Check for horizontal win on the current line
    bool win_line = true;
    for (int c = 0; c < grid_size; c++)
    {
        if (Board[row][c] != current_player)
        {                     // If any cell is not current player
            win_line = false; // Horizontal win not possible
            break;
        }
    }
    if (win_line)
    {
        return true; // Player wins horizontally
    }

    // Check for vertical win on the current column
    bool win_col = true;
    for (int l = 0; l < grid_size; l++)
    {
        if (Board[l][col] != current_player)
        {                    // If any cell is not current player
            win_col = false; // Vertical win not possible
            break;
        }
    }
    if (win_col)
    {
        return true; // Player wins vertically
    }

    // Check the main diagonal on the current column
    if (row == col)
    {
        bool winDiag1 = true;
        for (int i = 0; i < grid_size; i++)
        {
            if (Board[i][i] != current_player)
            {
                winDiag1 = false;
                break;
            }
        }
        if (winDiag1)
            return true;
    }

    // Check the anti-diagonal on the current column
    if (row + col == grid_size - 1)
    {
        bool winDiag2 = true;
        for (int i = 0; i < grid_size; i++)
        {
            if (Board[i][grid_size - 1 - i] != current_player)
            {
                winDiag2 = false;
                break;
            }
        }
        if (winDiag2)
            return true;
    }

    // No win detected
    return false;
}

bool TicTacToe::Tie()
{
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (Board[i][j] == '_')
            {
                return false; // At least one empty cell -> not a tie
            }
        }
    }
    return true; // All cells are filled
}

vector<pair<int, int>> TicTacToe::getEmptyCells()
{
    std::vector<std::pair<int, int>> empty_cells = {};

    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (Board[i][j] == '_')
            {
                empty_cells.push_back(std::make_pair(i, j));
            }
        }
    }
    return empty_cells;
}

pair<int, int> TicTacToe::getComputerMove()
{
    if (difficulty == 1) // Easy difficulty: random move
    {
        vector<pair<int, int>> empty_cells = getEmptyCells();
        if (!empty_cells.empty()) // check if there are empty cells
        {
            int randomIndex = rand() % empty_cells.size(); // chose a random index to select an empty cell
            return empty_cells[randomIndex];               // returns (row, col) of the selected cell
        }
    }
    if (difficulty == 2) // Hard difficulty: minimax agent
    {
        // Hard difficulty logic can be implemented here
        return BestMove(); 
    }
    return {0, 0};
}

pair<int, int> TicTacToe::ChosePosition()
{
    int row, col;
    int choice = -1;
    cout << "Chose a position : " << endl;
    cin >> choice;

    while (choice < 1 || choice > grid_size * grid_size)
    {
        cout << "Choice of of range. Chose a position :"
             << endl;
        cin >> choice;
    }

    row = (choice - 1) / grid_size;
    col = (choice - 1) % grid_size;

    return {row, col};
}

bool TicTacToe::playMove(int row, int col)
{
    if (Board[row][col] != '_')
    {
        return false;
    }

    Board[row][col] = current_player;

    return true;
}

pair<bool, int> TicTacToe::Play()
{
    pair<bool, int> result = {true, 0}; // first: continue game, second: continue/win/tie/lose status
    int row, col;
    displayBoard();

    if (difficulty == 0 || current_player == 'X')
    {
        pair<int, int> pos = ChosePosition();
        row = pos.first;
        col = pos.second;

        if (Board[row][col] != '_')
        {
            cout << "Invalid choice, cell already occupied. Try again.\n"
                 << endl;
            return {true, 0}; // Continue the game
        }
    }
    else
    {
        // Computer player's turn
        pair<int, int> move = getComputerMove();
        row = move.first;
        col = move.second;
        cout << "Computer chose position: " << (row * grid_size + col + 1) << '\n'
             << endl;
    }

    // Place the move on the board
    Board[row][col] = current_player;

    if (Win(row, col, current_player)) // Check if this move wins the game
    {
        displayBoard();
        if (difficulty > 0 && current_player == 'O')
        {
            cout << "YOU LOSE...COMPUTER WINS\n"
                 << endl;      // Announce computer victory
            return {false, 3}; // Lost status
        }
        else
        {
            cout << "PLAYER '" << current_player << "' WINS\n"
                 << endl;      // Announce victory
            return {false, 1}; // Win status
        }
    }

    if (Tie()) // Check for Tie
    {
        displayBoard();
        cout << "It is a tie, play again!\n"
             << endl;      // Tie message
        return {false, 2}; // Stop the game & Tie status
    }

    Switchplayer(); // Switch to the next player
    return result;  // Continue game
}

void TicTacToe::Session(int number_of_games)
{
    while (number_of_games > 0)
    {
        Board_Reset();
        current_player = 'X'; // X always starts first

        pair<bool, int> continue_game;
        continue_game.first = true;
        while (continue_game.first)
        {
            continue_game = Play(); // Play() returns (continue, win)=(true, 1)
        }
        number_of_games--;
        if (number_of_games == 0)
        {
            cout << "Session over! Thanks for playing!" << endl;
            break;
        }
        char response;
        cout << "Next game ? (y/n):";
        cin >> response;
        if (response == 'n' || response == 'N')
        {
            cout << "Thanks for playing!" << endl;
            break;
        }
        else if (response == 'y' || response == 'Y') // play next game
        {
            cout << "\nStarting next game...\n"
                 << endl;
            switch (continue_game.second) // adjust grid size based on last game result
            {
            case 1: // win, increase grid size
                if (grid_size < 6)
                {
                    grid_size++;
                }
                break;
            case 3: // lose, decrease grid size
                grid_size = 3;
                break;
            case 2: // tie, replay with same grid size
                break;
            default:
                break;
            }
            Board_Reset();
        }
    }
}

// Evaluates whether the given player has achieved a winning state.
// This is used after simulating a move inside the minimax algorithm.
bool TicTacToe::WinState(char current_player)
{
    // Check all rows
    for (int i = 0; i < grid_size; ++i) 
    {
        bool Check = true;
        for (int j = 0; j < grid_size; ++j) 
        {
            if (Board[i][j] != current_player) 
            {   
                Check = false; 
                break; 
            }
        }
        if (Check) 
        {
            return true;
        }
    }

    // Check all columns
    for (int j = 0; j < grid_size; ++j) 
    {
        bool Check = true;
        for (int i = 0; i < grid_size; ++i) 
        {
            if (Board[i][j] != current_player) 
            {   
                Check = false; 
                break; 
            }
        }
        if (Check) 
        {
            return true;
        }
    }

    // Check the main diagonal
    bool Check = true;
    for (int i = 0; i < grid_size; ++i) 
    {
        if (Board[i][i] != current_player) 
        {   
            Check = false; 
            break; 
        }
    }
    if (Check)
    {
        return true;
    } 

    // Check the anti-diagonal
    Check = true;
    for (int i = 0; i < grid_size; ++i) 
    {
        if (Board[i][grid_size - 1 - i] != current_player) 
        { 
            Check = false;
            break; 
        }
    }
    if (Check) 
    {
        return true;
    }

    return false;
}



// Minimax algorithm with alpha-beta pruning.
// The AI ('O') tries to maximize the score, while the human ('X') tries to minimize it.
// Depth is used both to limit recursion and to reward faster wins.
// Randomness is injected to make the AI less predictable.
int TicTacToe::Minimax(bool isMaximizing, int Depth, int alpha, int beta)
{   
    // Terminal evaluation: AI wins
    if (WinState('O'))
    {
        return 10 - Depth;
    }

    // Terminal evaluation: Human wins
    if (WinState('X'))
    {
        return -(10 - Depth);
    }

    // Draw or depth limit reached
    if (Tie() || Depth == 0)
    {
        return 0;
    }

    // Maximizing player (AI)
    if (isMaximizing)
    {
        int val = -100;

        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                if (Board[i][j] == '_')
                {
                    // Simulate move
                    Board[i][j] = 'O';

                    int score = Minimax(false, Depth - 1, alpha, beta);

                    // Add slight randomness to prevent deterministic play
                    score += (rand() % 7) - 3;

                    // Undo move
                    Board[i][j] = '_';

                    val = max(val, score);
                    alpha = max(alpha, val);

                    // Alpha-beta pruning
                    if (beta <= alpha)
                    {
                        return val;
                    }
                }
            }
        }
        return val;
    }

    // Minimizing player (Human)
    else
    {
        int val = 100;

        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                if (Board[i][j] == '_')
                {
                    // Simulate move
                    Board[i][j] = 'X';

                    int score = Minimax(true, Depth - 1, alpha, beta);

                    // Slight randomization
                    score += (rand() % 7) - 3;

                    // Undo move
                    Board[i][j] = '_';

                    val = min(val, score);
                    beta = min(beta, val);

                    // Alpha-beta pruning
                    if (beta <= alpha)
                    {
                        return val;
                    }
                }
            }
        }
        return val;
    }
}



// Computes the best move for the AI using minimax and optional randomness.
// Returns a pair {row, column}.
std::pair<int,int> TicTacToe::BestMove()
{
    int bestScore = 100;
    std::pair<int,int> bestMove = {-1, -1};

    // Set search depth depending on board size
    int Depth = 0;

    if (grid_size <= 3)
    {
        randomChance = 70;  // 70% chance to make a random move on small boards
        Depth = 3;
    } 
    else
    {
        Depth = 4;
    }

    // Random move to avoid fully predictable AI
    if (rand() % 100 < randomChance)
    {
        auto cells = getEmptyCells();
        return cells[rand() % cells.size()];
    }

    // Evaluate all possible moves
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            if (Board[i][j] == '_')
            {
                Board[i][j] = 'O';

                int score = Minimax(false, Depth, -5, 5);

                Board[i][j] = '_';

                // Keep the move with the highest score
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }

    // Failsafe in case no move was selected
    if (bestMove.first == -1)
    {
        auto cells = getEmptyCells();
        return cells[rand() % cells.size()];
    }

    return bestMove;
}
