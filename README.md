# Tic-Tac-Toe C++ (Morpion in french)

This project is an implementation of the classic **Tic-Tac-Toe** (Noughts and Crosses) game in C++.

## Project structure

1. **Phase one (current)** : basic 3x3 game against ourselves [OK]
2. **Phase two** : Dynamic levels against computer (random and intelligent agents) [IN PROGRESS]
3. **Phase three** : Graphical implementation [OK]

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
