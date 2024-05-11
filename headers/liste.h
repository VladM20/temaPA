#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player
{
    char *firstName;
    char *secondName;
    int points;
} Player;

typedef struct Member
{
    Player player;
    struct Member *next;
} Member;

typedef struct Team
{
    int numberOfPlayers;
    char *teamName;
    Member *members;
    struct Team *next;
} Team;

Team *createTeam();
void addTeam(Team**,Team*);
void removeTeam(Team*);