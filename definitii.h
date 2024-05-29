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

//teams.c

//Testeaza daca a fost alocata memorie (returneaza 0 daca POINTER e NULL).
int allocWorked(void *pointer,char *function);
//Returneaza 1(true) daca fisierul FILE nu a putut fi deschis.
int verifyFile(FILE *file,char *fileName);
//Gaseste cea mai mare putere a lui 2 mai mica decat n.
int powerOf2(int n);
//Sterge ' '(space),'\n','\r', daca sunt, din NAME.
void truncateWhiteSpace(char *name);
//Calculeaza scorul echipei.
void teamPoints(Team *team);
//Citeste numele unei echipe si il aloca dinamic.
char *readTeamName(FILE *input);
//Citeste un nume al unui jucator si il aloca dinamic.
char *readName(FILE *input);
//Citeste si returneaza un player din fisierul INPUT. 
Player readPlayer(FILE *input);
//Returneaza, cu alocare dinamica, o copie a vectorului de playeri din SOURCE.
Player *copyPlayers(Player *source,int numberOfPlayers);
//Elibereaza memoria alocata vectorului PLAYERS de dimensiune NUMBEROFPLAYERS.
void freePlayers(Player *players,int numberOfPlayers);
//Aloca memorie si returneaza pointer catre aceasta.
Team *allocTeam();
//Citeste si returneaza o echipa din fisierul INPUT.
Team *readTeam(FILE *input);
//Copiaza, cu alocare dinamica, echipa SOURCE in echipa DESTINATION.
void copyTeam(Team *source,Team *destination);

//liste.c

//Adauga echipa TEAM in LIST.
void listAdd(Team *team,Node **list);
//Creeaza lista de echipe si o populeaza cu date din fisier.
Node *createList(FILE *input,int *numberOfTeams);
//Cauta punctajul cel mai mic din LIST.
float minPoints(Node *list,int numberOfTeams);
//Elibereaza memoria alocata pentru TEAM;
void freeTeam(Team *team);
//Sterge nodul *LIST.
void deleteNode(Node **list);
//Sterge echipa cu punctajul MINPOINTS.
void deleteLastTeam(Node **list,float minPoints);
//Sterge lista de echipe.
void deleteList(Node **list);
//Returneaza o copie alocata dinamic a SOURCE.
Node *copyList(Node *source);

//cozi.c

typedef struct Match
{
    Team *team1,*team2;
    struct Match *next;
} Match;

typedef struct Queue
{
    Match *front,*rear;
} Queue;

//Verifica daca coada Q este goala.
int isEmpty(Queue *q);
//Creeaza o coada goala.
Queue *createQueue();
//Returneaza o copie a continutului LIST.
Queue *ListToQueue(Node *list);
//Adauga un meci in coada.
void enQueue(Queue *q,Team *team1,Team *team2);
//Scoate din coada un meci (doua echipe).
void deQueue(Queue *q,Team **team1,Team **team2);
//Sterge coada de meciuri.
void deleteQueue(Queue **q);
//Returneaza o coada populata de elementele din STACK.
Queue *queueFromStack(Node *stack);

//stive.c

//Adauga o echipa in stiva.
void push(Node **top,Team *team);
//Scoate o echipa din stiva.
Team *pop(Node **top);
//Sterge o stiva din memorie.
void deleteStack(Node **stack);

//tasks.c

//Scrie in fisierul OUTPUT continutul LIST.
void writeTeams(FILE* output,Node *list,int numberOfTeams);
//Simuleaza un meci si pune echipele in stivele corespunzatoare.
void playMatch(Team *team1,Team *team2,Node **winners,Node **losers);
//Scrie in fisierul OUTPUT un numar de NUMBEROFSPACES spatii.
void addSpaces(FILE *output,int numberOfSpaces);
//Scrie in fisierul OUTPUT titlul rundei ROUNDNUMBER.
void writeRoundHeader(FILE *output,int roundNumber);
//Scrie in fisierul OUTPUT un meci.
void writeMatch(FILE *output,Team *team1,Team *team2);
//Scrie in fisierul OUTPUT castigatorii rundei ROUNDNUMBER.
void writeWinners(FILE* output,Node *stack,int roundNumber);
//Executa cerinta pentru task 2.
void task2(int *numberOfTeams,Node **list);
//Executa cerintele pentru task 3.
void task3(FILE *output,int *numberOfTeams,Node **list,Node **last8Teams);
//Executa cerintele pentru task 4.
void task4(FILE *output,Node **last8Teams);

//bst.c

typedef struct TreeNode
{
    Team *team;
    struct TreeNode *left,*right;
} TreeNode;

//Returneaza un nod nou populat de echipa TEAM. 
TreeNode *newNode(Team *team);
//Insereaza in arborele reprezentat de NODE echipa TEAM.
TreeNode *insert(TreeNode *node,Team *team);

//In main; pentru debugging.

void printQ(Queue *q);
void printTeams(Node *list);