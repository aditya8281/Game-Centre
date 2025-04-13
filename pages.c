#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "header.h"

void Page1();
void Page2();
void game();

void Page2()
{
    system("clear||cls");
    printf("%s===========%sGAME CENTRE%s===========%s\n\n",BLUE,RED,BLUE,RESET);
    
    printf("Which game you want to play...\n\n");
    printf("1. 2048\n2. Mine Sweeper\n3. tictactoe\n\n");
    printf("\nEnter B to Log Out\nEnter E to Exit\n\n");
    printf("Enter Your Choice: ");



    char n;
    scanf(" %c",&n);

    if(n=='1')
    {
        system("clear||cls");
        m2048();

    }
    else if(n=='2')
    {
        system("clear||cls");
        mMineSweeper();
    }
    else if(n=='3')
    {
        system("clear||cls");
        mtictactoe();
    }
    else if(n=='B'||n=='b')
    {
        system("clear||cls");
        game();

    }
    else if(n=='E'||'e')
    {
        exit(0);
    }
    else
    {
        printf("Invalid Input!!!");
    }
    return;

}

void login()
{
    char storedName[50];
    char storedPass[50];
    char name[50];
    char pass[50];

    int success=0;

    firse:

    system("clear ||cls");
    
    FILE *info = fopen("information.txt","r");

    if(info==NULL)
    {
        printf("Error while opening file");
        return;
    }

    printf("%s===========%sGAME CENTRE%s===========%s\n\n",BLUE,RED,BLUE,RESET);

    printf(">Enter your User name: ");
    scanf(" %s",name);
    printf(">Enter your Password: ");
    scanf(" %s",pass);

    while(fscanf(info,"%s %s",storedName,storedPass) != EOF)
    {
        if((strcmp(storedName,name)==0) && (strcmp(storedPass,pass)==0))
        {
            success = 1;
            break;
        }

    }
    if(success==0)
    {
        printf("Invalid Credentials...\n");
        char in;
        printf(">1. Exit\n 2. Back\n 3. retry\n\n>Enter your choice: ");
        scanf(" %c",&in);
        if(in=='1')
        {
            exit(0);
        }
        else if(in=='2')
        {
            system("clear||cls");
            Page1();
        }
        else if(in=='3')
        goto firse;

        
    }
    fclose(info);
    return;
    
}


void reg()
{

    char storedName[50];
    char storedPass[50];
    char name[50];
    char pass[50];

    reg:

    system("clear||cls");
    printf("%s===========%sGAME CENTRE%s===========%s\n\n",BLUE,RED,BLUE,RESET);
    

    printf(">Enter your User name: ");
    scanf(" %s",name);
    printf(">Enter your Password: ");
    scanf(" %s",pass);
    FILE *info = fopen("information.txt","r");
    
    if(info==NULL)
    {
        printf("Error while opening file");
        return;
    }

    while(fscanf(info,"%s %s",storedName,storedPass) != EOF)
    {
        if((strcmp(storedName,name)==0) && (strcmp(storedPass,pass)==0))
        {
            printf("Already Exists!!!\n\n");
            char in;
            printf(">1. Exit\n 2. Back\n 3. retry\n\n>Enter your choice: ");
            scanf(" %c",&in);
            if(in=='1')
            {
                exit(0);
            }
            else if(in=='2')
            {
                system("clear||cls");
                Page1();
            }
            else if(in=='3')
            {
                fclose(info);
                goto reg;
            }
        }

    }
    fclose(info);
    info = fopen("information.txt","a");
    
    if(info==NULL)
    {
        printf("Error while opening file");
        return;
    }


    fprintf(info,"%s %s\n",name,pass);
    fclose(info);

}

void Page1()
{
    printf("%s===========%sGAME CENTRE%s===========%s\n\n",BLUE,RED,BLUE,RESET);
    printf(">1. Login\n 2. Register\n 3. Exit\n\n");
    printf(">Enter your choice: ");
    char in;
    
    do
    {
        scanf(" %c",&in);
        if(in!='1'&&in!='2'&&in!='3')
        {
            printf("INVALID INPUT!!!");
        }
        else break;
    } while (in!='1'&&in!='2'&&in!='3');

    if(in=='1')
    {
        login();
    }
    else if(in=='2')
    {
        reg();
    }
    else if(in=='3')
    {
        exit(0);
    }
    return;
}
