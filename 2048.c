#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "header.h"

void Page2();

#define MAXRANDOMVALUE 3

int arr[4][4] = { 0 }, c[4], temp = 0, len = 0, score = 0,
    highscore = 0, count = 0,
    ch = 0;



// fun to find length/ in other file , just called  here//
int findlen(int n);



// basic printing
void print()
{
    int i, j, k, len1;
    printf("%s===========%sGAME CENTRE%s===========%s\n\n",BLUE,RED,BLUE,RESET);

    printf(
        "\n===============2048==============\n");
    printf("YOUR SCORE=%d\n", score);

    // highscore
    if (score < highscore) {
        printf("HIGH SCORE=%d\n", highscore);
    }
    else {
        highscore = score;
        printf("HIGH SCORE=%d\n", highscore);
    }


// printing of board
    printf("\n---------------------------------\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (j == 0) {
                printf("|");
            }
            if (arr[i][j] != 0) {
                len1 = findlen(arr[i][j]);
                // printf("%d:",len);

                for (k = 0; k < 4 - len; k++) {
                    printf(" ");
                }
                printf("%d", arr[i][j]);

                for (k = 0; k < 4 - len; k++) {
                    printf(" ");
                }
                for (k = 0; k < len - 1; k++) {
                    printf(" ");
                }
                printf("|");
            }
            else {
                for (k = 0; k < 8 - 2 * len - 1; k++) {
                    printf(" ");
                }
                printf("|");
            }
            len = 0;
        }
        if (i != 3) {
            printf("\n---------------------------------\n");
        }
    }
    printf(
        "\n---------------------------------\n");


// printing basic options
    printf(">RESTART-> R\n");
    printf(" Back-> B\n");
    printf(" EXIT-> E\n");
    printf(" ENTER YOUR CHOISE -> W,S,A,D\n");
}




//shift of all the numbers according to the player//adding of numbers too
void movevalue(int k)
{
    int i;
    if (k == 3) {
        return;
    }
    for (i = k; i < 4; i++) {
        if (c[i] != 0) {
            movevalue(i + 1);
            for (; i < 4; i++) {
                if (c[i + 1] != 0) {
                    break;
                }
                c[i + 1] = c[i];
                c[i] = 0;
            }
        }
    }
}

int findlen(int n)
{

    if (n == 0) {

        return len;
    }
    else {
        len++;
        findlen(n / 10);
    }
}



// adding of 2 or 4 based on probability everytime after player makes a move
void addrandomno()
{
    int no;
    srand(time(NULL));
    int i, j; 
    do {
        i = (rand()) % (MAXRANDOMVALUE + 1);
        j = (rand()) % (MAXRANDOMVALUE + 1);// using probability
    } while (arr[i][j] != 0);
    no = ((rand() % 10) + 1);
    if (no >5) {
        arr[i][j] = 4;
    }
    else {
        arr[i][j] = 2;
    }
}




// updating the array
void rupdate()
{
    int i, j;
    for (i = 3; i > 0; i--) {
        if (c[i] == c[i - 1]) {
            c[i] += c[i - 1];
            score = score + c[i];
            temp = 1;
            c[i - 1] = 0;
        }
        else if (c[i - 1] == 0 && c[i] != 0) {
            c[i - 1] = c[i];
            c[i] = 0;
            temp = 1;
        }
        else if (c[i] == 0) {
            temp = 1;
        }
    }
    movevalue(0);
}



// reset the game
void resetgame()
{
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            arr[i][j] = 0;
        }
    }
    system("clear || cls");
    score = 0;
    addrandomno();
}



// main fun
int m2048()
{
    int i, j, k, m, n, same = 0;
    char choise, restart;

    //basic printing
    printf("%s==========%sGAME ARENA%s==========%s\n\n",BLUE,RED,BLUE,RESET);
    printf("===============2048==============\n");
    printf("WELCOME TO PUZZLE 2048\n");
    printf("> CONTROLS\n");
    printf("  FOR MOVES:- 'W','S','A','D'\n");
    printf("  RESTART THE GAME:- 'R'\n");
    printf("  Back:- 'B'\n");
    printf("  EXIT:-'E'\n\n");

    printf("\nPRESS ANY KEY TO START THE GAME....");

    getchar();
    system("clear || cls");

    FILE* ptr;
    ptr = fopen("highscore.txt", "r");// acessing the highscore text file
    
    if(ptr==NULL) printf("File didn't open!!"); return 0;
    
    fscanf(ptr, "%d", &highscore);
    fclose(ptr);
    addrandomno();
    print();
    while (1) {
        if (score >= highscore) {

            ptr = fopen("highscore.txt", "w");
            fprintf(ptr, "%d", score);
            fclose(ptr);
        }
        choise = getchar();
        while (getchar() != '\n')
         ;

        //basic playing controls
        if (choise == 'D' || choise == 'd') {
            count++;
            ch++;
            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    c[j] = arr[i][j];
                }
                rupdate();
                for (k = 0; k < 4; k++) {
                    arr[i][k] = c[k];
                }
            }
        }
        else if (choise == 'a' || choise == 'A') {
            count++;
            ch++;
            for (i = 0; i < 4; i++) {
                for (j = 3; j >= 0; j--) {
                    c[3 - j] = arr[i][j];
                }
                rupdate();
                for (k = 0; k < 4; k++) {
                    arr[i][3 - k] = c[k];
                }
            }
        }
        else if (choise == 's' || choise == 'S') {
            count++;
            ch++;

            for (i = 0; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    c[j] = arr[j][i];
                }
                rupdate();
                for (k = 0; k < 4; k++) {
                    arr[k][i] = c[k];
                }
            }
        }
        else if (choise == 'w' || choise == 'W') {
            count++;
            ch++;

            for (i = 0; i < 4; i++) {
                for (j = 3; j >= 0; j--) {
                    c[3 - j] = arr[j][i];
                }
                rupdate();
                for (k = 0; k < 4; k++) {
                    arr[3 - k][i] = c[k];
                }
            }
        }


            // rest of controls
        else if (choise == 'R' || choise == 'r') {
            count = 0;
            resetgame();
            print();
            continue;
        }

        else if(choise == 'b' || choise == 'B')
        {
            system("clear||cls");
            Page2();
        }
        else if (choise == 'e' || choise == 'E') {
            exit(0);
        }

        if (temp == 1) {
            temp = 0;
            system("clear || cls");
            printf("\n%c\n", choise);
            addrandomno();
            print();
        }
        else if (temp == 8) {
            temp = 0;
            print();
        }
        else {
            for (m = 0; m < 4; m++) {
                for (n = 3; n > 0; n--) {
                    if (arr[m][n] == arr[m][n - 1]
                        || arr[m][n] == 0
                        || arr[m][n - 1] == 0) {
                        same = 1;
                        break;
                    }
                    if (arr[n][m] == arr[n - 1][m]
                        || arr[m][n] == 0
                        || arr[m][n - 1] == 0) {
                        same = 1;
                        break;
                    }
                }
                if (same == 1)
                    break;
            }
            if (same == 1) {
                printf("\n============INVALID "
                       "KEY==========\n");
                same = 0;
            }
            else {
                //end printing
                printf(
                    "\n=============GAME OVER============");
                printf("\nWANT TO PLAY MORE?? Y/N??\n");
                restart = getchar();
                
                switch (restart) {
                case 'Y':
                case 'y':
                    resetgame();
                    print();
                    break;
                case 'n':
                case 'N':
                    system("clear||cls");
                    Page2();
                }
                continue;
            }
        }
    
    }
    return 0;
}
