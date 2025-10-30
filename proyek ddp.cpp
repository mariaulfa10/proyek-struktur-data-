#include <stdio.h>
#include <stdbool.h>
#include <ctime>
#define SIZE 3

// Inisialisasi papan permainan
void initBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Cetak papan permainan
void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---|---|---\n");
    }
    printf("\n");
}

// Cek apakah ada yang menang
bool checkWin(char board[SIZE][SIZE], char player) {
    for (int i = 0; i < SIZE; i++) {
        // Cek baris dan kolom
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Cek diagonal
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

// Cek apakah papan penuh
bool isBoardFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

// Jalankan game
void playGame() {
    char board[SIZE][SIZE];
    initBoard(board);

    char currentPlayer = 'X';
    bool gameOver = false;

    printf("Selamat datang di Tic Tac Toe!\n");
    while (!gameOver) {
        printBoard(board);
        printf("Giliran pemain %c.\n", currentPlayer);

        // Input posisi
        int row, col;
        do {
            printf("Masukkan baris dan kolom (1-3): ");
            scanf("%d %d", &row, &col);
            row--; col--;
        } while (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ');

        // Update papan
        board[row][col] = currentPlayer;

        // Cek kondisi game
        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            printf("Pemain %c menang!\n", currentPlayer);
            gameOver = true;
        } else if (isBoardFull(board)) {
            printBoard(board);
            printf("Permainan seri!\n");
            gameOver = true;
        } else {
            // Ganti giliran pemain
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

int main() {
    playGame();
    return 0;
}
