#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100
#define ROUND_PADDING 33
#define WINNER_PADDING 34

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
    Player *player;
} Team;

typedef struct Node
{
    Team *team;
    struct Node *next;
} Node;
//Testeaza daca a fost alocata memorie.
int allocWorked(void *pointer,char *function);

//Citeste numele unei echipe fara \n.
char *readTeamName(FILE *input);
//Elimina spatiile de la finalul numelui.
void truncateWhiteSpace(char *name);
//Citeste un nume al unui jucator.
char *readName(FILE *input);

Team *initializeTeam(int numberOfPlayers);

Player *initializePlayers(int numberOfPlayers);
//Adauga o echipa din fisier.
void addTeam(FILE *input,Node **list);
//Copiaza echipa din source in destination.
void copyTeam(Team *source,Team *destination);
//Creeaza lista de echipe din fisier.
Node *fcreateList(FILE *input,int *numberOfTeams);
//Calculeaza punctajul echipei.
void teamPoints(Team *team);
//Cauta punctajul cel mai mic.
float minPoints(Node *list,int numberOfTeams);

void deleteTeam(Team **team);
//Sterge jucatorii si restul echipei.
void deleteTeamData(Node **team);
//Sterge o singura echipa, in functie de punctaj.
void deleteLastTeam(Node **list,float minPoints);
//Sterge lista de echipe.
void deleteList(Node **list);

void duplicateList(Node *source,Node **destination);

//task 3: Cozi

typedef struct Match
{
    Team *team1,*team2;
    struct Match *next;
} Match;

typedef struct Queue
{
    Match *front,*rear;
} Queue;

//Creeaza coada de meciuri cu echipe din LIST.
Queue *createQueue(Node *list);
//Verifica daca coada q este goala.
int isEmpty(Queue *q);
//Adauga un meci in coada.
void enQueue(Queue *q,Team *team1,Team *team2);
//Scoate cele doua echipe ale unui meci din coada in LEFT si RIGHT.
void deQueue(Queue *q,Team **team1,Team **team2);
//Sterge coada de meciuri.
void deleteQueue(Queue **q);

Queue *queueFromStack(Node *stack);

//task 3: Stive

//Adauga o echipa in stiva.
void push(Node **top,Team *team);
//Scoate o echipa din stiva.
Team *pop(Node **top);

void printTeams(Node *list);