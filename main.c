#include<stdio.h>
#include<stdlib.h>

#include "header.h"

int main()
{
    
    printf("Which game you want to play...\n");
    printf("1. 2048\n2. Mine Sweeper\n3. tictactoe\n");
    printf("\nEnter B to Go back to previous page\nEnter E to Exit\n");



    char n;
    scanf("%c",&n);

    if(n=='1')
    {
        m2048();

    }
    else if(n=='2')
    {
        mMineSweeper();
    }
    else if(n=='3')
    {
        mtictactoe();
    }
    else if(n=='B'||n=='b')
    {

    }
    else if(n=='E'||'e')
    {
        exit(0);
    }
    else
    {
        printf("Invalid Input!!!");
    }
    return 0;

    
}