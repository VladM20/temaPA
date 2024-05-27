#include "definitii.h"

void push(Node **top,Team *team)
{
    Node *newTeam=(Node*)malloc(sizeof(Node));
    if(!allocWorked(newTeam,"push(newTeam)"))
        return;
    newTeam->team=(Team*)malloc(sizeof(Team));
    if(!allocWorked(newTeam->team,"push(newTeam->team)"))
        return;
    copyTeam(team,newTeam->team);
    newTeam->next=*top;
    *top=newTeam;
}

Team *pop(Node **top)
{   
    if(*top==NULL || (*top)->team==NULL)
        return NULL;

    Node *temp=*top;
    *top=(*top)->next;
    Team *team=(Team*)malloc(sizeof(Team));
    if(!allocWorked(team,"pop(team)"))
        return NULL;
    copyTeam(temp->team,team);
    deleteTeamData(&temp);
    return team;
}