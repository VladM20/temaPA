#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

//task 1 & 2: Liste

typedef struct Player
{
    char *firstName;
    char *secondName;
    int points;
} Player;

typedef struct Team
{
    int numberOfPlayers;
    float points;
    char *name;
    Player player[10];
} Team;

typedef struct List
{
    Team *team;
    struct List *next;
} List;

//Citeste numele unei echipe fara \n.
int readTeamName(FILE *input,char *dest,int length);
//Adauga o echipa din fisier.
void addTeam(FILE *input,List **list);
//Creeaza lista de echipe.
List *createList(FILE *input,int *numberOfTeams);
//Calculeaza punctajul echipei.
void teamPoints(Team *team);
//Cauta punctajul cel mai mic.
float minPoints(List *list,int numberOfTeams);
//Sterge jucatorii si restul echipei.
void deleteTeamData(List **team);
//Sterge o singura echipa, in functie de punctaj.
void deleteTeam(List **list,float minPoints);
//Sterge lista de echipe.
void deleteList(List **list);

//task 3: Cozi

typedef struct Match
{
    Team left,right;
    struct M *next;
} Match;

typedef struct Queue
{
    Match *front,*rear;
} Queue;

Queue *createQueue();

void enQueue(Queue *q,Team left,Team right);