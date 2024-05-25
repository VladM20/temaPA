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

typedef struct Node
{
    Team *team;
    struct Node *next;
} Node;

//Citeste numele unei echipe fara \n.
int readTeamName(FILE *input,char *dest,int length);
//Adauga o echipa din fisier.
void addTeam(FILE *input,Node **list);
//Creeaza lista de echipe.
Node *createList(FILE *input,int *numberOfTeams);
//Calculeaza punctajul echipei.
void teamPoints(Team *team);
//Cauta punctajul cel mai mic.
float minPoints(Node *list,int numberOfTeams);
//Sterge jucatorii si restul echipei.
void deleteTeamData(Node **team);
//Sterge o singura echipa, in functie de punctaj.
void deleteTeam(Node **list,float minPoints);
//Sterge lista de echipe.
void deleteList(Node **list);

//task 3: Cozi

typedef struct Match
{
    Team *left,*right;
    struct Match *next;
} Match;

typedef struct Queue
{
    Match *front,*rear;
} Queue;

//Creeaza coada de meciuri cu echipe din LIST.
Queue *createQueue(Node *list);
//Adauga un meci in coada.
void enQueue(Queue *q,Team *left,Team *right);
//Scoate cele doua echipe ale unui meci din coada in LEFT si RIGHT.
void deQueue(Queue *q,Team *left,Team *right);
//Sterge coada de meciuri.
void deleteQueue(Queue *q);

//task 3: Stive

//Adauga o echipa in stiva.
void push(Node **top,Team *team);