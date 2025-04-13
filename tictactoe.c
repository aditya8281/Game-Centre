#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "header.h"

void Page2();

#define PLAYER 'X'
#define COMPUTER 'O'
#define EMPTY ' '

char boardT[3][3];// globally defined

// Color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"


// player1 yellow     player2 green
//player   yellow     computer green
//general statement blue
//error statement red

void printBoardT(int winner);
int isBoardFull();
int checkWinner(int player);
void playerMove();
void computerMove(); 




int mtictactoe() {

    printf("%s==========%sGAME ARENA%s==========%s\n\n",BLUE,RED,BLUE,RESET);

    int player;
    int winner = 0;

    // Initialize 3x3 board with empty spaces
     for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            boardT[i][j]=' ';
        }
    }    
    
    do
    {
        printf(BLUE);
        printf(">Enter 1 if you want to play with computer or Enter 2 if you want to play with friend:\n");   //changed play alone to play with computer
        printf(RESET);
        scanf("%d",&player);
        if (player!=1 && player!=2)
        {
            printf(RED);
            printf("WRONG INPUT!!!\n");
            printf(RESET);
        }
        
    } while (player!=1 && player!=2);
    

    if (player==1){
        while (1) {
            printBoardT(winner);
    
            
            playerMove();
            // check if player wins or not
            winner = checkWinner(player);
            if (winner != 0 || isBoardFull()==1) break;
            computerMove();
            // check if comp wins or not
            winner = checkWinner(player);                                
            if (winner != 0 || isBoardFull()==1) break;
    }

    printBoardT(winner);}

    else if(player==2){
        int currentPlayer = 1; // Player 1 starts first
        int choice, row, col;
        char mark;
    
        while (1) {
            printBoardT(winner);
            currentPlayer = (currentPlayer % 2!=0) ? 1 : 2; // switch between players
            mark = (currentPlayer == 1) ? 'X' : 'O'; // Player 1 is 'X' and Player 2 is 'O'
    
            int row, col;
            while (1) {
                if(mark=='X'){
                    printf(YELLOW);
                    printf("> Player %d :Enter your move (row [1-3] and column [1-3]): ",currentPlayer);
                    printf(RESET);
                } else{
                    printf(GREEN);
                    printf("> Player %d :Enter your move (row [1-3] and column [1-3]): ",currentPlayer);
                    printf(RESET);
                }
                scanf("%d %d", &row, &col);
                row--; col--; // input to array no changing like 0-1 etc.
    
                if (row >= 0 && row < 3 && col >= 0 && col < 3 && boardT[row][col] == ' ') {
                    boardT[row][col] = mark;
                    break;
                } else {
                    printf(RED);
                    printf("Invalid move!!!, try again.\n");
                    printf(RESET);
                }
            }
            // Check for draw
            if (isBoardFull()==1) {
                printBoardT(winner);
                break;
            }

            // winner check
            if (checkWinner(player)) {
                printBoardT(winner);
                break;
            }
    
            currentPlayer++; // switching the player
        }
    }


    // basic buttons
    printf(BLUE);
    printf("1. Restart\n2. Exit Game\n3. Exit App\n");
    printf(RESET);
    char in;
    scanf(" %c",&in);
    if(in=='1')
    {
        system("clear || cls");  //Screen clear karva maate
        mtictactoe();
    }

    if(in=='2')
    {
        Page2();
    }

    if(in=='3')
    {
        exit(0);
    }


    return 0;
}
 


// Print the Tic-Tac-Toe board
void printBoardT(int winner) {     
    if(winner==0)
    {
        //system("clear||cls");
    }
    printf("\n"); 
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", boardT[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("___|___|___\n");
    }
    printf("   |   |   ");
    printf("\n"); 
}
   

// Check if the board is full
int isBoardFull() {
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (boardT[i][j] == EMPTY){
                return 0;
            }    
        }
    }
    printf("\n");
    printf("IT IS A DRAW!");
    printf("\n");       
    return 1;
}
    

// Check for a winner (returns 'X', 'O', or 0 for no winner)
int checkWinner(int player) {                                    //modified to adapt to two players
    for (int i = 0; i < 3; i++) {
        // Check rows
        if (boardT[i][0] == boardT[i][1] && boardT[i][1] == boardT[i][2] && boardT[i][0] != EMPTY) {
            if(player==1){
                if(boardT[i][0] =='X'){
                  printf("\n");
                  printf(BLUE); 
                  printf("YOU WIN!\n");
                  printf(RESET); 
                  printf("\n");
                }     
               if(boardT[i][0] =='O'){
                  printf("\n");
                  printf(BLUE); 
                  printf("COMPUTER WINS!\n");
                  printf(RESET); 
                  printf("\n");
                } 
            } else{
                if(boardT[i][0] =='X'){
                  printf("\n");
                  printf(BLUE);
                  printf("PLAYER 1 WINS!\n"); 
                  printf(RESET);  
                  printf("\n");
                }
                if(boardT[i][0] =='O'){
                  printf("\n");
                  printf(BLUE);
                  printf("PLAYER 2 WINS!\n");
                  printf(RESET);
                  printf("\n");
                } 
            }   
            return 1;     
        }
        // Check columns
        if (boardT[0][i] == boardT[1][i] && boardT[1][i] == boardT[2][i] && boardT[0][i] != EMPTY) {
            if(player==1){
                if(boardT[0][i] =='X'){
                  printf("\n");
                  printf(BLUE);  
                  printf("YOU WIN!\n");
                  printf(RESET); 
                  printf("\n");
                }     
               if(boardT[0][i] =='O'){
                  printf("\n");
                  printf(BLUE); 
                  printf("COMPUTER WINS!\n");
                  printf(RESET); 
                  printf("\n");
                } 
            } else{
                if(boardT[0][i] =='X'){
                  printf("\n");
                  printf(BLUE);
                  printf("PLAYER 1 WINS!\n");   
                  printf(RESET);
                  printf("\n");
                }
                if(boardT[0][i] =='O'){
                  printf("\n");
                  printf(BLUE);
                  printf("PLAYER 2 WINS!\n");
                  printf(RESET);
                  printf("\n");
                } 
            }   
            return 1;
        }
    }




    // Check diagonals
    if (boardT[0][0] == boardT[1][1] && boardT[1][1] == boardT[2][2] && boardT[0][0] != EMPTY) {
         if(player==1){
                if(boardT[0][0] =='X'){
                  printf("\n");
                  printf(BLUE);  
                  printf("YOU WIN!\n");
                  printf(RESET);  
                  printf("\n");
                }     
               if(boardT[0][0] =='O'){
                  printf("\n");
                  printf(BLUE); 
                  printf("COMPUTER WINS!\n");
                  printf(RESET);
                  printf("\n");
                } 
            } else{
                if(boardT[0][0] =='X'){
                  printf("\n");
                  printf(BLUE);
                  printf("PLAYER 1 WINS!\n");   
                  printf(RESET);
                  printf("\n");
                }
                if(boardT[0][0] =='O'){
                  printf("\n");
                  printf(BLUE);
                  printf("PLAYER 2 WINS!\n");
                  printf(RESET);
                  printf("\n");
                } 
            }   
            return 1;
    }
    if (boardT[0][2] == boardT[1][1] && boardT[1][1] == boardT[2][0] && boardT[0][2] != EMPTY) {
         if(player==1){
                if(boardT[0][2] =='X'){
                  printf("\n");
                  printf(BLUE);  
                  printf("YOU WIN!\n");
                  printf(RESET);  
                  printf("\n");
                }     
               if(boardT[0][2] =='O'){
                  printf("\n");
                  printf(BLUE); 
                  printf("COMPUTER WINS!\n");
                  printf(RESET); 
                  printf("\n");
                } 
            } else{
                if(boardT[0][2] =='X'){
                  printf("\n");
                  printf(BLUE);
                  printf("PLAYER 1 WINS!\n");   
                  printf(RESET);
                  printf("\n");
                }
                if(boardT[0][2] =='O'){
                  printf("\n");
                  printf(BLUE);
                  printf("PLAYER 2 WINS!\n");
                  printf(RESET);
                  printf("\n");
                } 
            }   
            return 1;
    }

    return 0; // No winner
}



// Player makes a move
void playerMove() {
    int row, col;
    while (1) {
        printf(YELLOW);
        printf(">Enter your move (row [1-3] and column [1-3]): ");
        printf(RESET);
        scanf("%d %d", &row, &col);
        row--; col--; // Adjust for 0-based indexing

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && boardT[row][col] == EMPTY) {
            boardT[row][col] = PLAYER;
            break;
        } else {
            printf("Invalid move!!!, try again.\n");
        }
    }
}



// Simple algo for comp// rand()is for random generation present in stdlib.h
void computerMove() {
    srand(time(NULL));// comp time delay
    int row, col;
    printf(GREEN);
    printf("Computer is making a move...\n");
    printf(RESET);
    sleep(1);    
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (boardT[row][col] != EMPTY);
    
    boardT[row][col] = COMPUTER;
}
