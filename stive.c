#include "definitii.h"

void push(Node **top,Team *team)
{
    Node *newTeam=(Node*)malloc(sizeof(Node));
    newTeam->team=team;
    newTeam->next=*top;
    *top=newTeam;
}