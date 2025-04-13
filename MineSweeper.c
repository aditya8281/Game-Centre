#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

void Page2();

#define SIZE 9
#define MINES 10

// Color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

char board[SIZE][SIZE];
char mines[SIZE][SIZE];
int revealed[SIZE][SIZE];
int flagged[SIZE][SIZE];

int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

void initBoards() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '*';
            mines[i][j] = '0';
            revealed[i][j] = 0;
            flagged[i][j] = 0;
        }
}

void placeMines() {
    int count = 0;
    while (count < MINES) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;
        if (mines[x][y] == '0') {
            mines[x][y] = 'M';
            count++;
        }
    }
}

int countAdjacentMines(int x, int y) {
    int count = 0;
    for (int d = 0; d < 8; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && mines[nx][ny] == 'M')
            count++;
    }
    return count;
}

void reveal(int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || revealed[x][y] || flagged[x][y])
        return;

    revealed[x][y] = 1;
    int count = countAdjacentMines(x, y);
    board[x][y] = count + '0';

    if (count == 0) {
        board[x][y] = ' ';
        for (int d = 0; d < 8; d++) {
            reveal(x + dx[d], y + dy[d]);
        }
    }
}

void toggleFlag(int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || revealed[x][y])
        return;

    flagged[x][y] = !flagged[x][y];
}

void printBoard() {
    system("clear||cls");
    printf("%s==========%sGAME ARENA%s==========%s\n\n",BLUE,RED,BLUE,RESET);
    printf("\n    ");
    for (int i = 0; i < SIZE; i++) printf("%2d ", i);
    printf("\n   +");
    for (int i = 0; i < SIZE; i++) printf("---");
    printf("+\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%2d |", i);
        for (int j = 0; j < SIZE; j++) {
            if (flagged[i][j]) {
                printf(" %sF%s ", YELLOW, RESET);
            } else if (!revealed[i][j]) {
                printf(" * ");
            } else {
                char cell = board[i][j];
                if (cell == ' ') {
                    printf("   ");
                } else {
                    int num = cell - '0';
                    switch (num) {
                        case 1: printf(" %s1%s ", BLUE, RESET); break;
                        case 2: printf(" %s2%s ", GREEN, RESET); break;
                        case 3: printf(" %s3%s ", RED, RESET); break;
                        case 4: printf(" %s4%s ", CYAN, RESET); break;
                        case 5: printf(" %s5%s ", YELLOW, RESET); break;
                        default: printf(" %c ", cell); break;
                    }
                }
            }
        }
        printf("|\n");
    }

    printf("   +");
    for (int i = 0; i < SIZE; i++) printf("---");
    printf("+\n");
}

int isWin() {
    int covered = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (!revealed[i][j])
                covered++;
    return (covered == MINES);
}

void showFinalBoard() {
    printf("\nFinal Board:\n    ");
    for (int i = 0; i < SIZE; i++) printf("%2d ", i);
    printf("\n   +");
    for (int i = 0; i < SIZE; i++) printf("---");
    printf("+\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%2d |", i);
        for (int j = 0; j < SIZE; j++) {
            if (mines[i][j] == 'M') {
                printf(" %sM%s ", RED, RESET);
            } else if (board[i][j] == ' ') {
                printf("   ");
            } else {
                printf(" %c ", board[i][j]);
            }
        }
        printf("|\n");
    }

    printf("   +");
    for (int i = 0; i < SIZE; i++) printf("---");
    printf("+\n");
}

int mMineSweeper() {
    srand(time(NULL));
    int playing = 1;
    int reset=0;

    while (playing) {

        initBoards();
        placeMines();
        int gameOver = 0;

        while (!gameOver) {
            printBoard();
            printf("\nMenu:\n");
            printf("1. Reveal a cell\n");
            printf("2. Reset game\n");
            printf("3. Toggle flag on a cell\n");
            printf("4. Exit Game\n");
            printf("Choose an option: ");

            char option;
            scanf(" %c", &option);

            if (option == '1') {
                int x, y;
                printf("Enter coordinates to reveal (row col): ");
                scanf("%d %d", &x, &y);

                if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
                    printf("Invalid input. Try again.\n");
                    continue;
                }

                if (flagged[x][y]) {
                    printf("This cell is flagged. Unflag it first to reveal.\n");
                    continue;
                }

                if (mines[x][y] == 'M') {
                    printf("\n%sBOOM! You hit a mine!%s\n", RED, RESET);
                    showFinalBoard();
                    reset=1;
                    gameOver = 1;
                    break;
                }

                reveal(x, y);

                if (isWin()) {
                    printf("\n%sCongratulations! You've cleared the minefield!%s\n", GREEN, RESET);
                    showFinalBoard();
                    gameOver = 1;
                    break;
                }
            } else if (option == '2') {
                printf("%sGame has been reset.%s\n", CYAN, RESET);
                reset = 1;
                break;
            } else if (option == '3') {
                int x, y;
                printf("Enter coordinates to toggle flag (row col): ");
                scanf("%d %d", &x, &y);
                toggleFlag(x, y);
            } else if (option == '4') {
                printf("%sExiting game. Goodbye!%s\n", YELLOW, RESET);
                sleep(1);
                system("clear||cls");
                playing = 0;
                gameOver = 1;
                Page2();
            } else {
                printf("Invalid option. Try again.\n");
            }
        }
        if(reset==1)
        {

            printf("1. Back\n2. Restart\n3. Exit Game\n\nChoose Option: ");
            char in;
            in:
            scanf(" %c",&in);
            if(in=='1')
            {
                Page2();
            }
            else if(in=='2')
            {
                mMineSweeper();
            }
            else if(in=='3')
            {
                exit(0);
            }
            else{
                printf("Invalid Input");
                goto in;
            }
        }


    }

    return 0;
}
