# Tic-Tac-Toe C++ (Morpion in french)

This project is an implementation of the classic **Tic-Tac-Toe** (Noughts and Crosses) game in C++.

## Project structure

1. **Phase one (current)** : basic 3x3 game against ourselves [OK]
2. **Phase two** : Dynamic levels against computer (random and intelligent agents) [IN PROGRESS]
3. **Phase three** : Graphical implementation [OK]
4. **Add tests** : Write tests for both TicTacToe and Graphics classes. [OK]

Here is the project structure

```bash
TicTacToe
├─ CMakeLists.txt
├─ Makefile
├─ README.md
├─ include
│  ├─ Graphics.hpp
│  └─ TicTacToe.hpp
├─ src
│  ├─ Graphics.cpp
│  ├─ TicTacToe.cpp
│  └─ main.cpp
└─ tests
   └─ test_Graphics.cpp
   └─ test_TicTacToe.cpp
```

## Generate Doxygen documentation

At the root of the project

```bash
doxygen doxygenfile
```

Then to open the documentation

```bash
cd open documentation/html/index.html
```

## Compilation and Execution

This project uses a **Makefile** to automate the compilation process with `g++`.

Install [CMake](https://cmake.org/download/).

You will also need to install the **latest version** (v3) of [Catch2](https://catch2.org/#Installation) and the [SFML](https://www.sfml-dev.org/download/sfml/3.0.2/) library :

```bash
brew install sfml catch2 # MacOS
sudo apt install libsfml-dev catch2 # Ubuntu/Debian
```

To launch the game :

```bash
mkdir build
cd build
cmake ..
make
./PlayTicTacToe
```

To launch the tests :

```bash
cd build
./test_TicTacToe.cpp
./test_Graphics.cpp
```

## Useful git commands

The first time you work on this repo, retrieve the https or ssh link :

```bash
git clone <paste the link>
```

To pull the lastest updates on the main:

```bash
git pull origin main
```

To retreive modifications made in other branches :

```bash
git pull origin <name-of-the-branch-you-want-to-retrieve>
git merge <name-of-the-branch-to-merge-to> #conflicts may arise and need solving
```

To add any changes made in your branch :

```bash
git commit -m "A concise description of your modification"
git push origin <branch-name>
```

To merge a branch into main :

```bash
git checkout main
git pull origin main # retrieve latest version
git merge <branch-name> --no-edit # no-edit if you don't want to write a merge comment
git push origin main 
```
# TicTacToe - C++ Game

## 📋 Description

This project implements a TicTacToe game in C++ with several advanced features, including an artificial intelligence based on the Minimax algorithm with alpha-beta pruning, a variable grid size, and different game modes.

## ✨ Main Features

- **Three difficulty modes**:
  - Mode 0: Human vs Human
  - Mode 1: Easy (AI with random moves)
  - Mode 2: Hard (AI with Minimax algorithm)

- **Dynamic grid**: Grid size adapts based on results (3x3 to 6x6)
- **Multiple game sessions**: Ability to play several consecutive games
- **Console interface**: Clear display with cell numbering

## 🏗️ Code Structure

### Constructor

```cpp
TicTacToe(int level, int games)
```
Initializes the game with the difficulty level and desired number of games.

### Main Functions

#### Board Management

- **`displayBoard()`**: Displays the game board with numbered empty cells
- **`Board_Reset()`**: Resets the board to the current grid size
- **`getEmptyCells()`**: Returns a vector containing the coordinates of all empty cells

#### Game Logic

- **`playMove(int row, int col)`**: Executes a move on the board
- **`Win(int row, int col, char current_player)`**: Checks if the current player has won after their move
  - Checks the row, column, and both diagonals
- **`Tie()`**: Checks if the game is a draw (board full with no winner)
- **`Switchplayer()`**: Alternates between players 'X' and 'O'

#### Move Management

- **`ChosePosition()`**: Allows the human player to choose a position (1 to grid_size²)
- **`getComputerMove()`**: Determines the computer's move based on difficulty
  - Difficulty 1: Random move
  - Difficulty 2: Uses Minimax algorithm

#### Artificial Intelligence (Minimax)

- **`Minimax(bool isMaximizing, int Depth, int alpha, int beta)`**: 
  - Implements the Minimax algorithm with alpha-beta pruning
  - Player 'O' (AI) maximizes the score (+10 for win)
  - Player 'X' (human) minimizes the score (-10 for loss)
  - Search depth adjustable based on grid size

- **`WinState(char current_player)`**: Evaluates if a player has won (used in Minimax)
- **`BestMove()`**: Finds the best possible move for the AI by testing all moves

#### Game Loop

- **`Play()`**: Manages a complete game turn
  - Returns `{continue, status}` where status = 0 (continue), 1 (win), 2 (tie), 3 (loss)

- **`Session(int number_of_games)`**: Manages a complete session of multiple games
  - Adjusts grid size based on results:
    - Win: increases grid size (max 6x6)
    - Loss: resets to 3x3
    - Tie: maintains current size

## 🎮 How It Works

### Game Flow

1. The board is displayed with empty cells numbered from 1 to n²
2. Player 'X' always starts first
3. Each player places their symbol in turn
4. The game ends with a win, loss, or tie
5. The system offers to continue with a new game

### Minimax Algorithm

The AI uses an optimal strategy based on exploring the possibility tree:
- Evaluates all possible moves up to a certain depth
- Uses alpha-beta pruning to optimize performance
- Scores: +10 (AI win), -10 (player win), 0 (tie)

## 🔧 Getters and Setters

- `getGridSize()`, `setGridSize(int size)`: Grid size management
- `getCell(int row, int col)`: Gets the content of a cell
- `getCurrentPlayer()`, `setCurrentPlayer(char player)`: Current player management
- `getDifficulty()`: Gets the difficulty level
- `getNumberOfGames()`: Gets the number of games

## 📊 Important Member Variables

- `Board`: 2D matrix representing the game board
- `current_player`: Current player ('X' or 'O')
- `difficulty`: Difficulty level (0, 1, or 2)
- `grid_size`: Current grid size (static variable)
- `number_of_games`: Number of games in the session

## 💡 Technical Notes

- The code uses `std::vector` for dynamic grid management
- Random initialization with `srand(time(0))` for random moves
- Minimax search depth is set to 4 to balance performance and difficulty
- Positions are converted from linear numbering (1-9) to coordinates (row, col)

## 🚀 Usage

```cpp
// Usage example
TicTacToe game(2, 5);  // Hard difficulty, 5 games maximum
game.Session(5);       // Start game session
```
