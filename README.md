# Three Musketeers Game

This is a C program to play the Three Musketeers game, a classic board game involving strategic moves by the Musketeers and their enemies. The program allows players to initialize the game board, make moves, and save the game state. This was my first project in C.

## Table of Contents
- [Overview](#overview)
- [How to Run](#how-to-run)
- [Gameplay Instructions](#gameplay-instructions)
- [Code Structure](#code-structure)
- [References](#references)
- [Author](#author)
- [Version](#version)
- [Bugs](#bugs)

## Overview

The Three Musketeers game is played on a 5x5 grid with three Musketeers (`M`) and several enemy pieces (`o`). The goal for the Musketeers is to either get all three in the same row or column, or to eliminate all the enemy pieces. The enemy's goal is to trap all Musketeers so that they can't make any legal moves.

For more information about the Three Musketeers game, see the [Wikipedia page](https://en.wikipedia.org/wiki/Three_musketeers_(game)) and you can also play it online [here](https://www.onlinesologames.com/three-musketeers).

## How to Run

1. **Compile the Program**: Use a C compiler to compile the program.
    ```sh
    gcc threeMusketeers.c -o threeMusketeers
    ```

2. **Run the Program**: Provide the initial game board file as an argument.
    ```sh
    ./threeMusketeers board.txt
    ```

## Gameplay Instructions

- The game board is read from a file which contains the initial positions of the Musketeers (`M`), enemies (`o`), and empty spaces (`.`).
- Players take turns to move their pieces. Player 1 controls the Musketeers, and Player 2 controls the enemies.
- To make a move, enter the location of the piece you want to move and the direction you want it to move. Locations are indicated as a letter (A, B, C, D, E) followed by a number (1, 2, 3, 4, or 5). Directions are indicated as left, right, up, down (L/l, R/r, U/u, D/d).
    - Example: `A,5=L` or `a,5=l` to move a piece from the top right-hand corner to the row below.
- The game ends when the Musketeers either get in the same row/column, all enemies are captured, or the Musketeers are trapped.

## Code Structure

The program is divided into several functions:

- **Main Function**:
    - Initializes the game.
    - Reads the game board from a file.
    - Starts the game loop.

- **Operations**:
    1. **Initialize Game Grid**: `void readBoard(const char* filename, char board[N][N]);`
        - Reads the initial game board from a file.
    2. **Display Game Grid**: `void displayBoard(char board[N][N]);`
        - Displays the current game board.
    3. **Play the Game**: Contains multiple functions:
        - `bool musketeersInLine(char board[N][N]);`
        - `bool enemiesLeft(char board[N][N]);`
        - `bool musketeersStuck(char board[N][N]);`
        - `bool parseInput(const char* input, char* from_rowC, int* from_col, char* direction);`
        - `bool stopGame(const char* input);`
        - `bool isValidMove(char board[N][N], bool player1Turn, int from_row, int from_col, char direction);`
        - `void makeMove(char board[N][N], int from_row, int from_col, char direction);`
        - `void play(char board[N][N]);`
    4. **Save Game Grid**: `void writeBoard(const char* filename, char board[N][N]);`
        - Writes the current game board to a file.

## References

- [Wikipedia: Three Musketeers Game](https://en.wikipedia.org/wiki/Three_musketeers_(game))
- [Play Online: Three Musketeers](https://www.onlinesologames.com/three-musketeers)

## Author

- **Maria H.** / foroum

## Version

- 11/10/2023

## Bugs

- No known bugs.

## Notes

This was my first project in C back in 2023! In the repository I have also provided a supplementary file in which there are three txt boards so you can check it out yourself. Cheers.
