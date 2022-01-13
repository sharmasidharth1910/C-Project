#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

//1D array representing different blocks of the board
//Each number corresponds to its position on board
char square[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

//choice - Variable holding the entered position
//Player - Variable representing the current player
int choice = 0, player, chance = 0;

//Function that will check the board for the winning positions
//1 - represents that the game is over with a winner
//0 - represents that the game is over with a draw
//-1 - represents that the game is still going on
int checkForWin();

int cpu();

void pl_vs_cpu(char name[]);

int cond[8][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 5, 9}, {3, 5, 7}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}};

int priority[9] = {5, 9, 7, 3, 1, 4, 6, 2, 8};

int cpu_chance = 1;

int flagwin = 0;

int choose = 0;

int gameType;

//Function that will draw the board and update it on to the console
void displayBoard();

//Function that will make an entry to the board depending on the player (1 or 2)
void markBoard(char mark);

//Function that will read the playerData file to display the player score
void readPoints(char playerName[]);

//Function to update the player data in the playerData file
void updatePoints(char playerName[], int point);

//Function to check whether the player already exists in the database or not
int authenticatePlayer(char playerName[], char password[]);

//Function to create a new player
int createPlayer(char playerName[], char password[]);

int main()
{
    char name[20];
    char password[20];
    int result;
    int loginType;
    int playerValue;
    // system("cls");

    printf("1. Sign Up\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Please select an option : ");

    scanf("%d", &loginType);

    switch (loginType)
    {
    case 1:

        printf("Enter the username : ");
        scanf("%s", name);
        printf("Enter the password : ");
        scanf("%s", password);

        result = createPlayer(name, password);

        if (result == 1)
        {
            printf("\nSuccessfully signed up the user.\n");
            clock_t startTime = clock();
            while (clock() < (startTime + 2000))
                ;
            system("cls");
            break;
        }
        else
        {
            printf("There was some error in signing up the user. Aborting\n");
            exit(0);
            break;
        }

    case 2:

        printf("Enter the username : ");
        scanf("%s", name);
        printf("Enter the password : ");
        scanf("%s", password);

        result = authenticatePlayer(name, password);

        if (result == 1)
        {
            printf("\nSuccessfully logged in the user.\n");
            clock_t startTime = clock();
            while (clock() < (startTime + 2000))
                ;
            system("cls");
            break;
        }
        else if (result == -1)
        {
            printf("The credentials of the users didn't match. Please try again.\n");
            exit(0);
            break;
        }
        else
        {
            printf("There was some error in logging in the user. PLease try later.\n");
            exit(0);
            break;
        }

    case 3:
        exit(0);
        break;

    default:
        printf("Invalid Choice !\n");
        exit(0);
        break;
    }

    //Variable receiving the game status
    int gameStatus;

    char mark;

    printf("**********OPTIONS**********\n\n");
    printf("1. Player Vs CPU\n\n");
    printf("2. Player Vs Player\n\n");
    printf("3. Scorecard\n\n");
    printf("4. Exit \n\n");
    printf("Enter your choice : ");
    scanf("%d", &choose);

    if (choose == 1 || choose == 2)
    {
        printf("\nRedirecting to game window. Please wait........");
        clock_t startTime = clock();
        while (clock() < (startTime + 2000))
            ;
        system("cls");
    }

    if (choose == 1)
    {
        pl_vs_cpu(name);
    }
    else if (choose == 2)
    {
        player = 1;

        do
        {
            displayBoard();

            // change turns
            player = (player % 2) ? 1 : 2;

            // get input
            printf("Player %d, choose a block: ", player);
            scanf("%d", &choice);

            // set the correct character based on player turn
            mark = (player == 1) ? 'X' : 'O';

            // set board based on user choice or invalid choice
            markBoard(mark);

            //Check the game status for win, draw or continue
            gameStatus = checkForWin();

            player++;

        } while (gameStatus == -1);

        displayBoard();

        if (gameStatus == 1)
        {
            player -= 1;
            if (player == 1)
            {
                printf("==>\aPlayer %d win ", player);
                updatePoints(name, 1);
            }
            else
            {
                printf("==>\aPlayer %d win ", player);
                updatePoints(name, -1);
            }
        }
        else
        {
            printf("==>\aGame draw");
            updatePoints(name, 0);
        }
    }
    else if (choose == 3)
    {
        readPoints(name);
    }
    else if (choose == 4)
    {
        exit(0);
    }
    else
    {
        printf("Invalid Choice !!");
    }

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

    choose == 1 ? printf("Player (X)  -  CPU (O)\n\n\n") : printf("Player 1 (X)  -  Player 2 (O)\n\n\n");

    printf("         |     |     \n");
    printf("      %c  |  %c  |  %c \n", square[1], square[2], square[3]);

    printf("    _____|_____|_____\n");
    printf("         |     |     \n");

    printf("      %c  |  %c  |  %c \n", square[4], square[5], square[6]);

    printf("    _____|_____|_____\n");
    printf("         |     |     \n");

    printf("      %c  |  %c  |  %c \n", square[7], square[8], square[9]);

    printf("         |     |     \n\n");
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
        printf("%c", getch());
    }
}
int cpu()
{
    int i, j, k, check, row, flag = 0;
    if (cpu_chance > 2)
    {
        //printf("checking cpu chance to win");
        for (i = 0; i < 8; i++)
        {
            check = 0;
            for (j = 0; j < 3; j++)
            {
                if (square[cond[i][j]] == 'O')
                {
                    check++;
                }
                else if (square[cond[i][j]] == 'X')
                {
                    check--;
                }
            }
            if (check == 2)
            {
                row = i;
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            for (k = 0; k < 3; k++)
            {
                if (square[cond[row][k]] != 'O' && square[cond[row][k]] != 'X')
                {
                    square[cond[row][k]] = 'O';
                    return 0;
                }
            }
        }
    }
    //blocking
    if (chance)
    {
        //printf("checking cpu chance to block");
        for (i = 0; i < 8; i++)
        {
            check = 0;
            for (j = 0; j < 3; j++)
            {
                if (square[cond[i][j]] == 'X')
                {
                    check++;
                }
                else if (square[cond[i][j]] == 'O')
                {
                    check--;
                }
            }
            if (check == 2)
            {
                row = i;
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            for (k = 0; k < 3; k++)
            {
                if (square[cond[row][k]] != 'X' && square[cond[row][k]] != 'O')
                {
                    square[cond[row][k]] = 'O';
                    return 0;
                }
            }
        }
    }

    for (i = 0; i < 9; i++)
    {
        if (square[priority[i]] != 'O' && square[priority[i]] != 'X')
        {
            square[priority[i]] = 'O';
            return 0;
        }
    }

    return 0;
}

int createPlayer(char playerName[], char password[])
{
    FILE *ptr;
    ptr = fopen("playerData.txt", "a+");

    if (fprintf(ptr, "%s %s %d %d %d\n", playerName, password, 0, 0, 0))
    {
        fclose(ptr);
        return 1;
    }

    return 0;
}

void updatePoints(char playerName[], int point)
{
    FILE *ptr, *tempPtr;
    ptr = fopen("playerData.txt", "r");

    if (ptr == NULL)
    {
        printf("Couldn't open the file\n");
        return;
    }

    tempPtr = fopen("tempFile.txt", "w");
    char curPlayer[20];
    char curPassword[20];
    int totalGames;
    int won;
    int lost;

    if (tempPtr == NULL)
    {
        printf("Could Not open file\n");
        return;
    }

    while (fscanf(ptr, "%s %s %d %d %d", curPlayer, curPassword, &totalGames, &won, &lost) == 5)
    {
        if (strcmp(curPlayer, playerName) == 0)
        {
            totalGames += 1;
            if (point == 1)
            {
                won += 1;
            }
            else if (point == -1)
            {
                lost += 1;
            }
            // fscanf(ptr, "%d", &points);
            fprintf(tempPtr, "%s %s %d %d %d\n", curPlayer, curPassword, totalGames, won, lost);
        }
        else
        {
            fprintf(tempPtr, "%s %s %d %d %d\n", curPlayer, curPassword, totalGames, won, lost);
        }
    }

    if (fclose(ptr) != 0)
    {
        printf("There was some error in closing the player file");
    }
    if (fclose(tempPtr) != 0)
    {
        printf("There was some error in closing the temp file");
    }

    char playerFile[] = "playerData.txt";

    int res = remove(playerFile);

    if (res == 0)
    {
        printf("Successfully removed the file");
    }
    else
    {
        printf("\n%s\n", res);
    }
    if (rename("tempFile.txt", "playerData.txt") == 0)
    {
        printf("Successfully renamed the file.");
    }
}

int authenticatePlayer(char playerName[], char password[])
{
    FILE *ptr;

    ptr = fopen("playerData.txt", "r");

    if (ptr == NULL)
    {
        printf("Couldn't open the file, please try again later\n");
        return 0;
    }

    char curPlayer[20];
    char curPassword[20];

    while (fscanf(ptr, "%s %s %*d %*d %*d", &curPlayer, &curPassword) == 2)
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

    return -1;
}

void readPoints(char playerName[])
{
    FILE *ptr;
    ptr = fopen("playerData.txt", "r");
    char curPlayer[20];
    char pass[20];
    int totalGames;
    int won;
    int lost;

    if (ptr == NULL)
    {
        printf("Could Not open file\n");
        return;
    }

    while (fscanf(ptr, "%s %s %d %d %d", curPlayer, pass, &totalGames, &won, &lost) == 5)
    {
        if (strcmp(curPlayer, playerName) == 0)
        {
            printf("Total Games Played : %d\n", totalGames);
            printf("Games Won : %d\n", won);
            printf("Games Lost : %d\n", lost);
        }
    }

    fclose(ptr);
}

void pl_vs_cpu(char name[])
{
    int gameStatus;
    player = 0;

    do
    {
        displayBoard();
        if (chance % 2 != 0)
        {
            int status = cpu();
            flagwin = 0;
            gameStatus = checkForWin();
            cpu_chance++;
            chance++;
        }
        else
        {
            printf("Player choose a block : ");
            scanf("%d", &choice);
            markBoard('X');
            flagwin = 1;
            gameStatus = checkForWin();
            chance++;
            player++;
        }
    } while (gameStatus != 1 && chance < 9);
    displayBoard();
    if (gameStatus == 1 && flagwin == 0)
    {
        updatePoints(name, -1);
        printf("CPU IS WINNER");
    }
    else if (gameStatus == 1 && flagwin == 1)
    {
        updatePoints(name, 1);
        printf("PLAYER IS WINNER");
    }
    else
    {
        updatePoints(name, 0);
        printf("DRAW");
    }
}
