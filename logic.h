#ifndef _LOGIC__H
#define _LOGIC__H

#define BOARD_SIZE 3
#define EMPTY_CELL ' '
#define O_CELL 'o'
#define X_CELL 'x'

enum WinType {
    NO_WIN,
    ROW_WIN,
    COL_WIN,
    DIAG_WIN,
    ANTI_DIAG_WIN
};

struct Tictactoe {
    char board[BOARD_SIZE][BOARD_SIZE];
    char nextMove = O_CELL;
    WinType winType = NO_WIN;
    int winIndex = -1;

    void init() {
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++) board[i][j] = EMPTY_CELL;
    }

    void move(int row, int column) {
        if (row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE) {
            if (board[row][column] == EMPTY_CELL) {
                board[row][column] = nextMove;
                nextMove = (nextMove == O_CELL) ? X_CELL : O_CELL;
            }
        }
    }

    char checkWinner() {
        for (int i = 0; i < BOARD_SIZE; ++i)
            if (board[i][0] != EMPTY_CELL &&
                board[i][0] == board[i][1] &&
                board[i][1] == board[i][2]) {
                winType = ROW_WIN;
                winIndex = i;
                return board[i][0];
            }

        for (int j = 0; j < BOARD_SIZE; ++j)
            if (board[0][j] != EMPTY_CELL &&
                board[0][j] == board[1][j] &&
                board[1][j] == board[2][j]) {
                winType = COL_WIN;
                winIndex = j;
                return board[0][j];
            }

        if (board[0][0] != EMPTY_CELL &&
            board[0][0] == board[1][1] &&
            board[1][1] == board[2][2]) {
            winType = DIAG_WIN;
            return board[0][0];
        }

        if (board[0][2] != EMPTY_CELL &&
            board[0][2] == board[1][1] &&
            board[1][1] == board[2][0]) {
            winType = ANTI_DIAG_WIN;
            return board[0][2];
        }

        bool full = true;
        for (int i = 0; i < BOARD_SIZE; ++i)
            for (int j = 0; j < BOARD_SIZE; ++j)
                if (board[i][j] == EMPTY_CELL)
                    full = false;

        if (full) return 'D';

        winType = NO_WIN;
        return '\0';
    }
};

#endif
