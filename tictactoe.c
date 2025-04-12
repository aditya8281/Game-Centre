#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "header.h"

#define PLAYER 'X'
#define COMPUTER 'O'
#define EMPTY ' '

char boardT[3][3];// globally defined


void printBoardT();
int isBoardFull();
int checkWinner();
void playerMove();
void computerMove(); 




int mtictactoe() {

    int player;
    printf("Enter 1 if you want to play alone or Enter 2 if you want to play with friend:\n");
    scanf("%d",&player);

    if(player!=1 && player!=2){
        printf("WRONG INPUT\n");
        mtictactoe();
    }
    
    // do
    // {
    //     printf("Enter 1 if you want to play alone or Enter 2 if you want to play with friend:\n");
    //     scanf("%d",&player);
    //     if (player!=1 && player!=2)
    //     {
    //         printf("WRONG INPUT\n");

    //     }
        
    // } while (player!=1 && player!=2);
    

    if (player==1){

    int winner = 0;
    
    // make that board
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            boardT[i][j] = EMPTY;
    
    while (1) {
        printBoardT(winner);

        
        playerMove();
        
        winner = checkWinner();// check point-player
        if (winner != 0 || isBoardFull()==1) break;
        computerMove();
        
        winner = checkWinner();//chech piont comp
        if (winner != 0 || isBoardFull()==1) break;
    }

    printBoardT(winner);}

    if(player==2){
        int currentPlayer = 1; // Player 1 starts first
        int choice, row, col;
        char mark;
    
        // Initialize 3x3 board with empty spaces
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                boardT[i][j]=' ';
            }
        }    
    
        while (1) {
            printBoardT(NULL);
            currentPlayer = (currentPlayer % 2!=0) ? 1 : 2; // Toggle player (1 or 2)
            mark = (currentPlayer == 1) ? 'X' : 'O'; // Player 1 is 'X' and Player 2 is 'O'
    
            int row, col;
            while (1) {
                printf("Player %d :Enter your move (row [1-3] and column [1-3]): ",currentPlayer);

                scanf("%d %d", &row, &col);
                row--; col--; // Adjust for 0-based indexing
    
                if (row >= 0 && row < 3 && col >= 0 && col < 3 && boardT[row][col] == ' ') {
                    boardT[row][col] = mark;
                    break;
                } else {
                    printf("Invalid move, try again.\n");
                }
            }
            // Check if there's a winner
            if (checkWinner()) {
                printBoardT(NULL);
                printf("PLAYER %d WIN!\n", currentPlayer);   //add exclamation marks in arni's
                break;
            }
    
            // Check if the board is full (i.e., it's a draw)
            if (isBoardFull()) {
                printBoardT(NULL);
                printf("IT IS A DRAW!\n");   //correct arni's
                break;
            }
    
            currentPlayer++; // Switch to the next player
        }
    }

    printf("1. Enter R to Restart\n2. Enter E to Exit");
    char in;
    scanf(" %c",&in);
    if(in=='R'||in=='r')
    {
        system("clear || cls");  //Screen clear karva maate
        mtictactoe();
    }
    if(in=='E'||in=='e')
    {
        exit(0);
    }


    return 0;
}
 




// display of board// har ek bar jo input hai usske sath print karenga
void printBoardT(int winner) {
    if(winner==0)
    {
        system("clear||cls");// last vale ko clear karke new print
    }
    printf("\n"); 
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("\033[1;31m");
            printf(" %c ", boardT[i][j]);
            printf("\033[0m");
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("___|___|___\n");
    }
    printf("   |   |   ");
    printf("\n"); 
}
   

// Check board is full
int isBoardFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (boardT[i][j] == EMPTY) {
                return 0;
            }
            printf("\n");
            printf("IT IS A DRAW");
            printf("\n");
    return 1;
}
    

// Check for a winner (returns 'X', 'O', or 0 for no winner)
int checkWinner() {
    for (int i = 0; i < 3; i++) {

        
        // Check rows
        if (boardT[i][0] == boardT[i][1] && boardT[i][1] == boardT[i][2] && boardT[i][0] != EMPTY) {
            if(boardT[i][0] =='X'){
                printf("\n");
              printf("YOU WIN");
              printf("\n");
            }
           if(boardT[i][0] =='O'){
            printf("\n");
              printf("COMPUTER WINS");
              printf("\n");
            }
            return 1;
        }

        
        // Check columns
        if (boardT[0][i] == boardT[1][i] && boardT[1][i] == boardT[2][i] && boardT[0][i] != EMPTY) {
             if(boardT[0][i] =='X'){
                printf("\n");
              printf("YOU WIN");
              printf("\n");
            }
           if(boardT[i][0] =='O'){
            printf("\n");
              printf("COMPUTER WINS");
              printf("\n");
            }
            return 1;
        }
    }




    // Check diagonals
    if (boardT[0][0] == boardT[1][1] && boardT[1][1] == boardT[2][2] && boardT[0][0] != EMPTY) {
         if(boardT[0][0] =='X'){
            printf("\n");
              printf("YOU WIN");
              printf("\n");
            }
           if(boardT[0][0] =='O'){
            printf("\n");
              printf("COMPUTER WINS");
              printf("\n");
            }
            return 1;
    }
    if (boardT[0][2] == boardT[1][1] && boardT[1][1] == boardT[2][0] && boardT[0][2] != EMPTY) {
         if(boardT[1][1] =='X'){
            printf("\n");
              printf("YOU WIN");
              printf("\n");
            }
           if(boardT[1][1] =='O'){
            printf("\n");
              printf("COMPUTER WINS");
              printf("\n");
            }
            return 1;
    }

    return 0; // No winner
}



// Player makes a move
void playerMove() {
    int row, col;
    while (1) {
        printf("Enter your move (row [1-3] and column [1-3]): ");
        scanf("%d %d", &row, &col);
        row--; col--; // Adjust for array- 1to 0, etc

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && boardT[row][col] == EMPTY) {
            boardT[row][col] = PLAYER;
            break;
        } else {
            printf("Invalid move, try again.\n");
        }
    }
}



// comp move with time .h- random generation
void computerMove() {
    srand(time(NULL));
    int row, col;
    printf("Computer is making a move...\n");
    sleep(1);    
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (boardT[row][col] != EMPTY);
    
    boardT[row][col] = COMPUTER;
}

