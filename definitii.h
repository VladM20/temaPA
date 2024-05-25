#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50

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
    float teamPoints;
    char *teamName;
    Player player[10];
    struct Team *next;
} Team;

//Citeste numele unei echipe fara \n.
int readTeamName(FILE *input,char *dest,int length);
//Adauga o echipa din fisier.
void addTeam(FILE *input,Team **teams);
//Creeaza lista de echipe.
Team *createList(FILE *input,int *numberOfTeams);
//Calculeaza punctajul echipei.
void teamPoints(Team *team);
//Cauta punctajul cel mai mic.
float minPoints(Team *teams,int numberOfTeams);
//Sterge jucatorii si restul echipei.
void deleteTeamData(Team **team);
//Sterge o singura echipa, in functie de punctaj.
void deleteTeam(Team **teams,float minPoints);
//Sterge lista de echipe.
void deleteList(Team **teams);

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