/*
 * tic_tac_toe_minimax.c
 *
 * CS5008 summer 2026
 * Xin Wang, Dan Liu
 * Tic Tac Toe game with Minimax Algorithm and alpha-beta pruning.
 */

#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

#define SIZE 3
#define WIN_SCORE 10
#define INF INT_MAX

/*
 * Counts how many board positions (nodes) a search visits. Reset before each
 * search, then read afterward to compare pruning vs. no pruning.
 */
long nodeCount = 0;

/*
 * Running totals across every computer move in the game, so we can report the
 * overall pruning savings when the game ends.
 */
long totalNaiveNodes = 0;
long totalPrunedNodes = 0;

/*
 * This function checks if there are any moves left on the board.
 * @return 1 if there are moves left, 0 otherwise.
 */
int hasMovesLeft(const char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == ' ')
                return 1;
    return 0;
}

/*
 * This function evaluates the current state of the game board.
 * @return 10 if player X (computer) wins, -10 if player O (human) wins, 0 otherwise.
 */
int evaluate(const char board[SIZE][SIZE]) {
    // Check rows
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == 'X') {
                return WIN_SCORE;
            } else if (board[i][0] == 'O') {
                return -WIN_SCORE;
            }
        }
    }

    // Check columns
    for (int j = 0; j < SIZE; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            if (board[0][j] == 'X') {
                return WIN_SCORE;
            } else if (board[0][j] == 'O') {
                return -WIN_SCORE;
            }
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'X') {
            return WIN_SCORE;
        } else if (board[0][0] == 'O') {
            return -WIN_SCORE;
        }
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'X') {
            return WIN_SCORE;
        } else if (board[0][2] == 'O') {
            return -WIN_SCORE;
        }
    }

    // If no one has won, the game is a tie
    return 0;
}

/*
 * Plain minimax WITHOUT alpha-beta pruning. It explores the entire game tree,
 * so the number of nodes it visits is the "naive" baseline we compare against.
 * @param board The current state of the game board.
 * @param depth The current depth of the recursion.
 * @param isMax True if the current player is the maximizing player (X).
 * @return The best score for the current player.
 */
int minimaxNoPruning(char board[SIZE][SIZE], int depth, int isMax) {
    // Count this node in the total visited for this search.
    nodeCount++;

    int score = evaluate(board);

    // If the maximizing player has won, return the score
    if (score == WIN_SCORE) {
        return score - depth;
    }

    // If the minimizing player has won, return the score
    if (score == -WIN_SCORE) {
        return score + depth;
    }

    // If there are no moves left, return 0 (tie)
    if (!hasMovesLeft(board)) {
        return 0;
    }

    // Maxmizing player (X) turn
    if (isMax) {
        int best = -INF;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int val = minimaxNoPruning(board, depth + 1, 0);
                    board[i][j] = ' ';
                    if (val > best) {
                        best = val;
                    }
                }
            }
        }
        return best;
    }
    // Minimizing player (O) turn
    else {
        int best = INF;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int val = minimaxNoPruning(board, depth + 1, 1);
                    board[i][j] = ' ';
                    if (val < best) {
                        best = val;
                    }
                }
            }
        }
        return best;
    }
}

/*
 * This function is the minimax algorithm (with alpha-beta pruning) that calculates the best move for the current player.
 * @param board The current state of the game board.
 * @param depth The current depth of the recursion.
 * @param alpha The alpha value for alpha-beta pruning.
 * @param beta The beta value for alpha-beta pruning.
 * @param isMax True if the current player is the maximizing player, false otherwise.
 * @param bestRow If non-NULL, receives the row of the best move found at this call's cell loop.
 * @param bestCol If non-NULL, receives the column of the best move found at this call's cell loop.
 * @return The best score for the current player.
 */
int minimax(char board[SIZE][SIZE], int depth, int alpha, int beta, int isMax, int *bestRow, int *bestCol) {
    // Count this node in the total visited for this search.
    nodeCount++;

    int score = evaluate(board);

    // If the maximizing player has won, return the score
    if (score == WIN_SCORE) {
        return score - depth;
    }

    // If the minimizing player has won, return the score
    if (score == -WIN_SCORE) {
        return score + depth;
    }

    // If there are no moves left, return 0 (tie)
    if (!hasMovesLeft(board)) {
        return 0;
    }

    // If this is the maximizing player's turn
    if (isMax) {
        int best = -INF;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // Check if cell is empty
                if (board[i][j] == ' ') {
                    // Make the move
                    board[i][j] = 'X';
                    // Call minimax recursively and choose the maximum value
                    int val = minimax(board, depth + 1, alpha, beta, !isMax, NULL, NULL);
                    if (val > best) {
                        best = val;
                        // Only the caller's top-level cell loop asks for the
                        // move itself; recursive calls pass NULL here.
                        if (bestRow != NULL && bestCol != NULL) {
                            *bestRow = i;
                            *bestCol = j;
                        }
                    }
                    alpha = (alpha > best) ? alpha : best;
                    // Prune the search if alpha >= beta
                    if (alpha >= beta) {
                        // Undo the move
                        board[i][j] = ' ';
                        return best;
                    }
                    // Undo the move
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    // If this is the minimizing player's turn
    else {
        int best = INF;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                // Check if cell is empty
                if (board[i][j] == ' ') {
                    // Make the move
                    board[i][j] = 'O';
                    // Call minimax recursively and choose the minimum value
                    int val = minimax(board, depth + 1, alpha, beta, !isMax, NULL, NULL);
                    best = (best < val) ? best : val;
                    beta = (beta < best) ? beta : best;
                    // Prune the search if alpha >= beta
                    if (alpha >= beta) {
                        // Undo the move
                        board[i][j] = ' ';
                        return best;
                    }
                    // Undo the move
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

/*
 * This function makes the best move for the computer (X). It runs the search
 * twice on the SAME position. Once with alpha-beta pruning and once without,
 * so we can report how many branches (nodes) pruning eliminated.
 * @param board The current state of the game board.
 */
void makeBestMove(char board[SIZE][SIZE]) {
    int bestRow = -1;
    int bestCol = -1;

    // Search with alpha-beta pruning.
    // This search also records the best move.
    nodeCount = 0;
    minimax(board, 0, -INF, INF, 1, &bestRow, &bestCol);
    long prunedNodes = nodeCount;

    // Search the same board without pruning to get a baseline count.
    nodeCount = 0;
    minimaxNoPruning(board, 0, 1);
    long naiveNodes = nodeCount;

    // Calculate how many nodes were avoided during this move.
    long removedNodes = naiveNodes - prunedNodes;
    double percent;

    if (naiveNodes > 0) {
        percent = 100.0 * removedNodes / naiveNodes;
    } else {
        percent = 0.0;
    }

    // Add this move's counts to the game-long totals.
    totalNaiveNodes += naiveNodes;
    totalPrunedNodes += prunedNodes;

    printf("  Minimax without pruning explored : %ld nodes\n",
           naiveNodes);
    printf("  Minimax with alpha-beta pruning  : %ld nodes\n",
           prunedNodes);
    printf("  Pruning avoided                  : %ld nodes (%.1f%% fewer)\n",
           removedNodes, percent);

    if (bestRow != -1 && bestCol != -1) {
        board[bestRow][bestCol] = 'X';
    }
}

/*
 * Print the game pruning summary: total nodes the naive search would have
 * explored vs. what alpha-beta actually explored, across all computer moves.
 */
void printPruningSummary(void) {
    long removedNodes;
    double percent;

    removedNodes = totalNaiveNodes - totalPrunedNodes;
    if (totalNaiveNodes > 0) {
        percent = 100.0 * removedNodes / totalNaiveNodes;
    } else {
        percent = 0.0;
    }

    printf("\n===== Pruning summary for this game =====\n");
    printf("  Total nodes without pruning : %ld\n", totalNaiveNodes);
    printf("  Total nodes with pruning    : %ld\n", totalPrunedNodes);
    printf("  Total nodes removed       : %ld (%.1f%% fewer)\n",
           removedNodes, percent);
    printf("=========================================\n");
}

/*
 * Parse an "A1"-style coordinate into row and column indices.
 * Accepts a row letter A-C (case-insensitive) followed by a column digit 1-3,
 * for example "A1", "b2", "C3". Row A/B/C maps to 0/1/2; column 1/2/3 maps to
 * 0/1/2.
 * @param input The input string to parse.
 * @param row Pointer to where the row index will be stored.
 * @param col Pointer to where the column index will be stored.
 * @return 0 on success (writes *row and *col), -1 on out-of-range input.
 */
int parseMove(const char *input, int *row, int *col) {
    if (input == NULL || input[0] == '\0' || input[1] == '\0') {
        return -1;
    }

    char rowCh;
    char colCh;
    
    rowCh = (char)toupper((unsigned char)input[0]);
    colCh = input[1];

    // Anything after the two-character coordinate must be whitespace only.
    for (const char *p = input + 2; *p != '\0'; p++) {
        if (!isspace((unsigned char)*p)) {
            return -1;
        }
    }

    if (rowCh < 'A' || rowCh > 'C') return -1;
    if (colCh < '1' || colCh > '3') return -1;

    // Convert the row and column characters to 0-based indices
    *row = rowCh - 'A';
    *col = colCh - '1';
    return 0;
}

/*
 * This function prints the current state of the game board.
 * @param board The current state of the game board.
 */
void printBoard(const char board[SIZE][SIZE]) {
    printf("\n");
    // Column numbers across the top.
    printf("     1   2   3\n");
    for (int i = 0; i < SIZE; i++) {
        // Row letter down the left side.
        printf("  %c ", 'A' + i);
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("    ---+---+---\n");
    }
    printf("\n");
}

/*
 * Read one line of input into buffer (holding up to n characters, including the
 * terminator) and strip the trailing newline.
 * @return 1 on success, 0 on end-of-input.
 */
int readLine(char *buffer, int n) {
    if (fgets(buffer, n, stdin) == NULL) {
        return 0;
    }
    // fgets keeps the newline; remove it so buffer holds just what was typed.
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    return 1;
}

/*
 * Ask the player whether they want to move first.
 * @return 0 if the human (O) goes first (answered yes), 1 if the computer (X)
 *         goes first (answered no).
 */
int chooseFirstPlayer(void) {
    char answer[100];
    while (1) {
        printf("Do you want to go first? Type 'y' (yes) or 'n' (no): ");
        if (!readLine(answer, sizeof(answer))) {
            return 0; // end of input, default to the human going first
        }
        if (answer[0] == 'y' || answer[0] == 'Y') return 0; // you go first
        if (answer[0] == 'n' || answer[0] == 'N') return 1; // computer goes first
        printf("Please type 'y' or 'n'.\n");
    }
}

/*
 * The main function of the program.
 * This is where the game starts and runs.
 * @return 0 on successful completion.
 */
int main() {
    char exitBuffer[100];
    char board[SIZE][SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    printf("Tic Tac Toe Game\n\n");

    // Ask who moves first (1 = computer, 0 = you), then announce the fixed marks.
    int computerFirst = chooseFirstPlayer();
    printf("\nYou are O, the computer is X.\n");
    if (computerFirst) {
        printf("The computer goes first.\n");
    } else {
        printf("You go first.\n");
    }

    printf("\nHow to enter a move:\n");
    printf("  Type a cell as a ROW letter (A-C) followed by a COLUMN number (1-3).\n");
    printf("  See the labels on the board: rows are A, B, C; columns are 1, 2, 3.\n");
    printf("  Example: \"B2\" places your O in the center; \"A1\" is the top-left.\n");

    // If the computer goes first, it makes one opening move before the normal
    // human-then-computer loop begins.
    printBoard(board);
    if (computerFirst) {
        makeBestMove(board);
        printBoard(board);
    }

    while (1) {
        int row;
        int col;
        char input[100];

        printf("Your move -- enter a cell (e.g. B2): ");
        if (!readLine(input, sizeof(input))) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        if (parseMove(input, &row, &col) != 0) {
            printf("Invalid input. Use a row letter A-C and a column number 1-3 (e.g. B2).\n");
            continue;
        }
        if (board[row][col] != ' ') {
            printf("That cell is already taken. Try again.\n");
            continue;
        }
        board[row][col] = 'O';
        printBoard(board);

        if (evaluate(board) == -WIN_SCORE) {
            printf("You win!\n");
            printPruningSummary();
            break;
        }
        if (!hasMovesLeft(board)) {
            printf("It's a tie!\n");
            printPruningSummary();
            break;
        }

        makeBestMove(board);
        printBoard(board);

        if (evaluate(board) == WIN_SCORE) {
            printf("Computer wins!\n");
            printPruningSummary();
            break;
        }
        if (!hasMovesLeft(board)) {
            printf("It's a tie!\n");
            printPruningSummary();
            break;
        }
    }
    
    readLine(exitBuffer, sizeof exitBuffer);

    return 0;
}
