#ifndef HEADER_H
#define HEADER_H

#include "tictactoe.c"
#include "MineSweeper.c"
#include "2048.c"

// //tictactoe Global

// #define PLAYER 'X'
// #define COMPUTER 'O'
// #define EMPTY ' '

// char boardT[3][3];// globally defined

// //MineSweeper Global

// #define SIZE 9
// #define MINES 10

// // Color codes
// #define RESET   "\x1b[0m"
// #define RED     "\x1b[31m"
// #define GREEN   "\x1b[32m"
// #define YELLOW  "\x1b[33m"
// #define BLUE    "\x1b[34m"
// #define CYAN    "\x1b[36m"

// char board[SIZE][SIZE];
// char mines[SIZE][SIZE];
// int revealed[SIZE][SIZE];
// int flagged[SIZE][SIZE];

// int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
// int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

// // 2048 Global

// #define MAXRANDOMVALUE 3

// int arr[4][4] = { 0 }, c[4], temp = 0, len = 0, score = 0,
//     highscore = 0, count = 0,
//     ch = 0;

// main functions

int m2048();
int mMineSweeper();
int mtictactoe();


#endif