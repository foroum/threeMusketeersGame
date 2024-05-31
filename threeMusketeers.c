/**
 * @file threeMusketeers.c
 * @brief this program is to play the three musketeers game
 * @author Maria H. / foroum
 * @version 11/10/2023
 * @bug no known bugs
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

# define N 5
// Operation 1 (Initialize Game Grid)
void readBoard(const char* filename, char board[N][N]);
// Operation 2 (Display Game Grid)
void displayBoard(char board[N][N]);
// Operation 3 (PLaying the game)
bool musketeersInLine(char board[N][N]);
bool enemiesLeft(char board[N][N]);
bool musketeersStuck(char board[N][N]);
bool parseInput(const char* input, char* from_rowC, int* from_col, char* direction);
bool stopGame(const char* input);
bool isValidMove(char board[N][N], bool player1Turn, int from_row, int from_col, char direction);
void makeMove(char board[N][N], int from_row, int from_col, char direction);
void play(char board[N][N]);
// Operation 4 (Saving game grid)
void writeBoard(const char* filename, char board[N][N]);

/**
 * Main function of the program. It initializes the game, reads the game board from a file, and starts the game loop.
 *
 * @param argc: number of command-line arguments
 * @param argv: array of command-line arguments
 * @return 0 on successful execution
 */
int main(int argc, char *argv[]){
    printf("*** The Three Musketeers Game ***\n");
    printf("To make a move, enter the location of the piece you want to move,\n");
    printf("and the direction you want it to move. Locations are indicated as\n");
    printf("a letter (A, B, C, D, E) followed by a number (1, 2, 3, 4, or 5).\n");
    printf("Directions are indicated as left, right, up, down (L/l, R/r, U/u, D/d).\n");
    printf("For example, to move the Musketeer from the top right-hand corner\n");
    printf("to the row below, enter 'A,5 = L' or 'a,5=l'(without quotes).\n");
    printf("For convenience in typing, use lowercase letters.\n");

    char board[N][N];
    readBoard(argv[1], board);
    play(board);

    writeBoard("out-theBoard.txt", board);
    printf("Saving out-theBoard.txt...Done\n Au revoir!");

    return 0;
}
/**
 * Operation 1 (Initialize Game Grid)
 * Reads the initial game board from a file and populates the 'board' array.
 * If there are any errors exits with a message.
 *
 * @param filename: file name containing the game board content
 * @param board: 2D array representing the game board
 */
void readBoard(const char* filename, char board[N][N]){
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int ch;
            do {
                ch = fgetc(file);
            } while (ch != 'o' && ch != 'M' && ch!='.' && ch != EOF);

            if (ch == EOF) {
                printf("Unexpected end of file.\n");
                exit(1);
            }

            board[i][j] = (char)ch;
        }
    }

    fclose(file);
}
/**
 * Operation 2 (Display Game Grid)
 * Displays the current game board with proper formatting.
 *
 * @param board: 2D array representing the game board
 */
void displayBoard(char board[N][N]){
     printf("   1   2   3   4   5\n");
    printf(" +---+---+---+---+---+\n");
    for (int i = 0; i < N; i++) {
        printf("%c|", 'A' + i);
        for (int j = 0; j < N; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n +---+---+---+---+---+\n");
    }
}

/**
 * Checks if there are three Musketeers in a row or column on the game board.
 *
 * @param board: 2D array representing the game board
 * @return true if there are three Musketeers in the same row or column, false otherwise
 */
bool musketeersInLine(char board[N][N]) {

    for (int row = 0; row < N; row++) {
        int musketeerCount = 0;
        for (int col = 0; col < N; col++) {
            if (board[row][col] == 'M') {
                musketeerCount++;
            }
        }
        if (musketeerCount == 3) {
            return true;
        }
    }
    for (int col = 0; col < N; col++) {
        int musketeerCount = 0; 
        for (int row = 0; row < N; row++) {
            if (board[row][col] == 'M') {
                musketeerCount++;
            }
        }
        if (musketeerCount == 3) {
            return true;
        }
    }

    return false;
}
/**
 * Checks if there are any enemies ('o') left on the game board.
 *
 * @param board: 2D array representing the game board
 * @return true if there are enemies left, false if there are none
 */
bool enemiesLeft(char board[N][N]){
    for(int i = 0; i < N; i++)
        for(int j = 0; j< N; j++)
            if(board[i][j]=='o')
                return true;
            
    return false;
}
/**
 * Checks if the Musketeers are stuck and cannot make any valid moves.
 * Checks if Musketeer can move in any direction with bool canMoveLeft, canMoveRight,
 * canMoveUp and canMoveDown. If musketeer can move in any direction they are not stuck.
 *
 * @param board: 2D array representing the game board
 * @return true if all Musketeers are stuck, false if at least one Musketeer can make a move
 */
bool musketeersStuck(char board[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (board[row][col] == 'M') {
                bool canMoveLeft = (col > 0 && board[row][col - 1] == 'o');
                bool canMoveRight = (col < N - 1 && board[row][col + 1] == 'o');
                bool canMoveUp = (row > 0 && board[row - 1][col] == 'o');
                bool canMoveDown = (row < N - 1 && board[row + 1][col] == 'o');

                if (canMoveLeft || canMoveRight || canMoveUp || canMoveDown) {
                    return false;
                }
            }
        }
    }

    return true;
}
/**
 * Checks if the input signals a game stop condition.
 *
 * @param input: user's input string
 * @return true if the input signals a game stop, false otherwise
 */
bool stopGame(const char* input) {
    return (strcmp(input, "0,0=E\n") == 0 || strcmp(input, "0,0=e\n") == 0);
}
/**
 * Parses the user input to extract the row, column, and direction of the move.
 * Checks if user's input is correct and parses it.
 * Also converts row value and direction to uppercase for easier use in isValidMove.
 * 
 * @param input: user's input string
 * @param from_row: pointer to store the extracted row character
 * @param from_col: pointer to store the extracted column (as an integer)
 * @param direction: pointer to store the extracted direction character
 * @return true if parsing is successful, false otherwise
 */
bool parseInput(const char* input, char* from_row, int* from_col, char* direction) {
    if (sscanf(input, "%c,%d=%c", from_row, from_col, direction) != 3) {
        printf("Invalid input format. Please use the format 'i,j=value'.\n");
        printf("i is a character between A-E (accepts both low and upper), j is a number between 1-5, and\n");
        printf("value is the direction wanted (L/l, R/r, U/u, or D/d).\n");
        return false;
    }

    *from_row = toupper(*from_row);
    *direction = toupper(*direction);

    return true;
}
/**
 * Checks if a move is valid by verifying if the source and destination coordinates are within bounds,
 * the direction is valid, and the move is allowed based on the game's rules.
 * If the move is wrong I made it print exact messages for each mistake.
 *
 * @param board: 2D array representing the game board
 * @param player1Turn: boolean indicating whether it's Player 1's turn (Musketeer) or not
 * @param from_row: source row of the move
 * @param from_col: source column of the move
 * @param direction: direction of the move
 * @return true if the move is valid, false if it's not
 */
bool isValidMove(char board[N][N], bool player1Turn, int from_row, int from_col, char direction) {
    if (from_row < 0 || from_row >= N || from_col < 0 || from_col >= N) {
        printf("Coordinates given are out of bounds!\n");
        return false;
    }

    char sourcePiece = board[from_row][from_col];
    char destinationPiece = ' ';

    if (direction != 'L' && direction != 'R' && direction != 'U' && direction != 'D') {
        printf("Invalid direction!\n");
        return false;
    }

    int to_row = from_row;
    int to_col = from_col;
    switch (direction) {
        case 'L':
            to_col--;
            break;
        case 'R':
            to_col++;
            break;
        case 'U':
            to_row--;
            break;
        case 'D':
            to_row++;
            break;
        default:
            printf("Invalid diection!\n");
            return false;
    }

    if (to_row < 0 || to_row >= N || to_col < 0 || to_col >= N) {
        printf("Move given is out of bounds!\n");
        return false;
    }

    destinationPiece = board[to_row][to_col];

    if (player1Turn) {
        if (sourcePiece != 'M') {
            printf("In the coodinates given there is no musketeer!\n");
            return false;
        }
        if (destinationPiece != 'o') {
            printf("You can't move there!\n");
            return false;
        }
    } else if (!player1Turn) {
        if (sourcePiece != 'o') {
            printf("In the coodinates given there is no enemy!\n");
            return false;
        }
        if (destinationPiece != '.') {
            printf("You can't move there!\n");
            return false;
        }
    } 

    return true;
}
/**
 * Makes the specified move on the game board by updating the source and destination positions.
 *
 * @param board: 2D array representing the game board
 * @param from_row: source row of the move
 * @param from_col: source column of the move
 * @param direction: direction of the move
 */
void makeMove(char board[N][N], int from_row, int from_col, char direction) {
    int to_row = from_row;
    int to_col = from_col;
    switch (direction) {
        case 'L':
            to_col--;
            break;
        case 'R':
            to_col++;
            break;
        case 'U':
            to_row--;
            break;
        case 'D':
            to_row++;
            break;
    }
    char piece = board[from_row][from_col];
    board[from_row][from_col] = '.';
    board[to_row][to_col] = piece;
}
/**
 * Operation 3 (the game)
 * The main game logic, where players take turns and make moves until the game ends.
 * It checks for winning conditions and manages player moves.
 * Starts with Player 1's turn. Displays the current game board.
 * Determines the current player's character ('M' for Player 1, 'o' for Player 2).
 * Read the player's move from input (e.g., "A,5=L"). Checks if game is wanted to stop.
 * If not, parses string, checks if move is valid, makes move and checks if anyone has won.
 * 
 * Repeats until one of the player ends game with '0,0=e'/'0,0=E' or if someone wins the game.
 *
 * @param board: 2D array representing the game board
 */
void play(char board[N][N]) {
    bool player1Turn = true;
    bool finished = false;
    while (!finished) {
        displayBoard(board);

        char currentPlayer = player1Turn ? 'M' : 'o';

        printf("Player %d, give %s's move:\n>", player1Turn ? 1 : 2, player1Turn ? "the Musketeer" : "the Enemy");

        char move[20];
        fgets(move, sizeof(move), stdin);

        if (stopGame(move)) {
            printf("Game stopped. Saving the game grid.\n");
            break;
        }

        char from_rowC;
        int from_col;
        char direction;

        if (!parseInput(move, &from_rowC, &from_col, &direction)) {
            continue;
        }


        int from_row = (int)(from_rowC - 'A');
        from_col = from_col - 1;

        if(!isValidMove(board, player1Turn, from_row, from_col, direction)){
            continue;
        }

        makeMove(board, from_row, from_col, direction);

        if((musketeersInLine(board) || !enemiesLeft(board))){
            printf("Cardinal Richelieu's men win!\n");
            finished = true;
        }
        else if(musketeersStuck(board) && !player1Turn){
            printf("The Musketeers win!\n");
            finished = true;
        }
        player1Turn = !player1Turn;
    }
}

/**
 * Operation 4 (Save Game Grid)
 * Writes the current game board to a file.
 *
 * @param filename: file name to save the game board to
 * @param board: 2D array representing the game board
 */
void writeBoard(const char* filename, char board[N][N]) {
    FILE* file = fopen(filename, "w"); // Open the file for writing
    if (file == NULL) {
        printf("Error opening the file for writing.\n");
        exit(1); // Exit with an error code
    }

    // Loop through the game board and write each character to the file
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fputc(board[i][j], file);
            if (j < N - 1) {
                fputc(' ', file); // Add space between columns
            }
        }
        fputc('\n', file); // Add a newline after each row
    }

    fclose(file); // Close the file
}