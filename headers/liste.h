#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

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
    Player player[];
    struct Team *next;
} Team;

void readTeamName(FILE*,char*,int);
Team *readTeam(FILE*);
void readMember(FILE*,Member**);

Team *createTeam();
void addTeam(Team**,Team*);
void removeTeam(Team*);