#include <stdlib.h>

typedef struct
{
    char *firstName;
    char *secondName;
    int points;
} Player;

typedef struct N
{
    Player player;
    struct N *next;
} Node;

typedef struct
{
    int numberOfPlayers;
    char *teamName;
    Player *player;
} Team;

