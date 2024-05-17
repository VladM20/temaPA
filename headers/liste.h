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
    float teamPoints;
    char *teamName;
    Player player[10];
    struct Team *next;
} Team;

//Citeste numele unei echipe fara \n.
int readTeamName(FILE*,char*,int);
//Adauga o echipa din fisier.
void addTeam(FILE*,Team**);
//Creeaza lista de echipe.
Team *createList(FILE*,int*);
//Calculeaza punctajul echipei.
void teamPoints(Team*);
//Cauta punctajul cel mai mic.
float minPoints(Team*,int);
//Sterge o singura echipa, in functie de punctaj.
void deleteTeam(Team**,);
//Sterge lista de echipe.
void deleteList(Team**);
