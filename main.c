#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1D array representing different blocks of the board
// Each number corresponds to its position on board
char square[10] = {'o', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

// choice - Variable holding the entered position
// Player - Variable representing the current player
int choice, player;

// Function that will check the board for the winning positions
// 1 - represents that the game is over with a winner
// 0 - represents that the game is over with a draw
//-1 - represents that the game is still going on
int checkForWin();

// Function that will draw the board and update it on to the console
void displayBoard();

// Function that will make an entry to the board depending on the player (1 or 2)
void markBoard(char mark);

// Function to handle the file operations to store, update and retrieve data
void readPoints(char playerName[]);
void updatePoints(char playerName[]);
int authenticatePlayer(char playerName[], char password[]);

int main()
{
    // Variable receiving the game status
    int gameStatus;

    char mark;

    player = 1;

    authenticatePlayer("Sneha", "123456");
    updatePoints("Piyush");
    getch();

    do
    {
        displayBoard();

        // change turns
        player = (player % 2) ? 1 : 2;

        // get input
        printf("Player %d, enter a number: ", player);
        scanf("%d", &choice);

        // set the correct character based on player turn
        mark = (player == 1) ? 'X' : 'O';

        // set board based on user choice or invalid choice
        markBoard(mark);

        // Check the game status for win, draw or continue
        gameStatus = checkForWin();

        player++;

    } while (gameStatus == -1);

    displayBoard();

    if (gameStatus == 1)
    {
        char winner[20] = "winner2";
        printf("==>\aPlayer %d win ", --player);
    }
    else
        printf("==>\aGame draw");

    getch();
    return 0;
}

int checkForWin()
{
    int returnValue = 0;

    if (square[1] == square[2] && square[2] == square[3])
    {
        returnValue = 1;
    }
    else if (square[4] == square[5] && square[5] == square[6])
        returnValue = 1;

    else if (square[7] == square[8] && square[8] == square[9])
        returnValue = 1;

    else if (square[1] == square[4] && square[4] == square[7])
        returnValue = 1;

    else if (square[2] == square[5] && square[5] == square[8])
        returnValue = 1;

    else if (square[3] == square[6] && square[6] == square[9])
        returnValue = 1;

    else if (square[1] == square[5] && square[5] == square[9])
        returnValue = 1;

    else if (square[3] == square[5] && square[5] == square[7])
        returnValue = 1;

    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
             square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] != '7' && square[8] != '8' && square[9] != '9')
        returnValue = 0;
    else
        returnValue = -1;

    return returnValue;
}

void displayBoard()
{
    system("cls");

    printf("\n\n\tTic Tac Toe\n\n");

    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");

    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);

    printf("     |     |     \n\n");
}

void markBoard(char mark)
{
    if (choice == 1 && square[1] == '1')
        square[1] = mark;

    else if (choice == 2 && square[2] == '2')
        square[2] = mark;

    else if (choice == 3 && square[3] == '3')
        square[3] = mark;

    else if (choice == 4 && square[4] == '4')
        square[4] = mark;

    else if (choice == 5 && square[5] == '5')
        square[5] = mark;

    else if (choice == 6 && square[6] == '6')
        square[6] = mark;

    else if (choice == 7 && square[7] == '7')
        square[7] = mark;

    else if (choice == 8 && square[8] == '8')
        square[8] = mark;

    else if (choice == 9 && square[9] == '9')
        square[9] = mark;
    else
    {
        printf("Invalid move ");

        player--;
        getch();
    }
}

// To get the points of a perticular player
void readPoints(char playerName[])
{
    FILE *ptr;
    ptr = fopen("fileName.txt", "r");
    char curPlayer[20];
    int points;

    if (ptr == NULL)
    {
        printf("Could Not open file\n");
        return;
    }

    while (fscanf(ptr, "%s %*s %d", &curPlayer, &points) == 2)
    {
        if (strcmp(curPlayer, playerName) == 0)
        {
            printf("%s's score is %d\n", curPlayer, points);
        }
    }

    fclose(ptr);
}

// To update the points of a player
void updatePoints(char playerName[])
{
    FILE *ptr, *tempPtr;
    ptr = fopen("fileName.txt", "r");

    if (ptr == NULL)
    {
        printf("Couldn't open the file, please try again later\n");
        return;
    }

    tempPtr = fopen("tempFile.txt", "w");
    char curPlayer[20];
    char curPassword[20];
    int points;

    if (tempPtr == NULL)
    {
        printf("Could Not open file\n");
        return;
    }

    while (fscanf(ptr, "%s %s %d", &curPlayer, &curPassword, &points) == 3)
    {
        if (strcmp(curPlayer, playerName) == 0)
        {
            // fscanf(ptr, "%d", &points);
            fprintf(tempPtr, "%s %s %d\n", curPlayer, curPassword, points + 10);
        }
        else
        {
            fprintf(tempPtr, "%s %s %d\n", curPlayer, curPassword, points);
        }
    }

    fclose(ptr);
    fclose(tempPtr);

    remove("fileName.txt");
    rename("tempFile.txt", "fileName.txt");
}

int authenticatePlayer(char playerName[], char password[])
{
    FILE *ptr;
    ptr = fopen("fileName.txt", "r+");

    if (ptr == NULL)
    {
        printf("Couldn't open the file, please try again later\n");
        return;
    }

    char curPlayer[20];
    char curPassword[20];

    while (fscanf(ptr, "%s %s %*d", &curPlayer, &curPassword) == 2)
    {
        if (strcmp(curPlayer, playerName) == 0)
        {
            if (strcmp(curPassword, password) == 0)
            {
                return 1;
            }
            return -1;
        }
    }

    fprintf(ptr, "%s %s %d\n", playerName, password, 0);
    fclose(ptr);
    return 0;
}
