#include "definitii.h"

void listAdd(Team *team,Node **list)
{
    if(team==NULL)
    {
        printf("Parametrii listAdd gresiti.\n");
        return;
    }
    
    Node *newNode=(Node*)malloc(sizeof(Node));
    if(!allocWorked(newNode,"listAdd(newNode)"))
        return;

    newNode->team=team;
    newNode->next=*list;   
    *list=newNode;
}

Node *createList(FILE *input,int *numberOfTeams)
{
    Node *list=NULL;
    fscanf(input,"%d",numberOfTeams);
    for(int i=0;i<*numberOfTeams;i++)
        listAdd(readTeam(input),&list);
    return list;
}

float minPoints(Node *list,int numberOfTeams)
{
    Node *temp=list;
    float min=list->team->points;
    for(int i=0;i<numberOfTeams && temp!=NULL;i++)
    {
        if(min>temp->team->points)
            min=temp->team->points;
        temp=temp->next;
    }
    return min;
}

void freeTeam(Team *team)
{
    if(team==NULL)
        return;
    if(team->name!=NULL)
        free(team->name);
    if(team->player!=NULL)
        freePlayers(team->player,team->numberOfPlayers);
    free(team);
}

void deleteNode(Node **list)
{
    if((*list)==NULL || (*list)->team==NULL)
        return;
    freeTeam((*list)->team);
    free((*list));
    *list=NULL;
}

void deleteLastTeam(Node **list,float minPoints)
{
    if(*list==NULL) 
        return;
    Node *temp=*list;
    if (temp->team->points==minPoints)
    {
        *list=(*list)->next;
        deleteNode(&temp);
        return;
    }
    Node* prev=*list;
    while(temp!=NULL)
    {
        if(temp->team->points!=minPoints)
        {
            prev=temp;
            temp=temp->next;
        } 
        else 
        {
            prev->next=temp->next;
            deleteNode(&temp);
            return;
        }
    }
}

void deleteList(Node **list)
{
    if(*list==NULL)
        return;

    Node *temp;
    while((*list)->next!=NULL)
    {
        temp=(*list)->next;
        deleteNode(list);
        *list=temp;
    }
    if((*list)->next==NULL)
        deleteNode(list);
}

Node *copyList(Node *source)
{
    if(source==NULL)
        return NULL;
    Node *destination=NULL;
    Node *current=source;
    while(current!=NULL)
    {
        Team *newTeam=(Team*)malloc(sizeof(Team));
        if(!allocWorked(newTeam,"duplicateList(newTeam)"))
            return NULL;

        copyTeam(current->team,newTeam);
        listAdd(newTeam,&destination);
        current=current->next;
    }
    return destination;
}