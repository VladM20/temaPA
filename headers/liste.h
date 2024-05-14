#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50

typedef struct Player
{
    char *firstName;
    char *secondName;
    int points;
} Player;

typedef struct Team
{
    int numberOfPlayers;
    char *teamName;
    Player player[10];
    struct Team *next;
} Team;

int readTeamName(FILE*,char*,int);
void addTeam(FILE*,Team**);
Team *createList(FILE*);