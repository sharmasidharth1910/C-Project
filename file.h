
#include <stdio.h>
#include <string.h>

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
                fclose(ptr);
                return 1;
            }
            fclose(ptr);
            return -1;
        }
    }

    fclose(ptr);
    return -1;
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
