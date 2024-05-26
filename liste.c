#include "definitii.h"

char *strdup(char *src) 
{
    char *dst=malloc(strlen(src)+1);
    strcpy(dst,src);
    return dst;
}

char *readTeamName(FILE *input)
{
    char name[MAX_LENGTH];
    fgets(name,MAX_LENGTH,input);
    truncateWhiteSpace(name);
    return strdup(name);
}

void truncateWhiteSpace(char *name)
{
    if(name==NULL)
        return;
    int length=strlen(name);
    while(length>0 && (name[length-1]==' ' || name[length-1]=='\n'))
        length--;
    name[length]='\0';
}

char *readName(FILE *input)
{
    char name[MAX_LENGTH];
    fscanf(input,"%s",name);
    truncateWhiteSpace(name);
    return strdup(name);
}

void addTeam(FILE *input,Node **list)
{
    Team *newTeam=(Team*)malloc(sizeof(Team));
    fscanf(input,"%d",&(newTeam->numberOfPlayers));
    fgetc(input);
    newTeam->player=(Player*)malloc(newTeam->numberOfPlayers*sizeof(Player));
    newTeam->name=readTeamName(input);
    for(int i=0;i<newTeam->numberOfPlayers;i++)
    {
        newTeam->player[i].firstName=readName(input);
        newTeam->player[i].secondName=readName(input);
        fscanf(input,"%d",&(newTeam->player[i].points));
    }
    teamPoints(newTeam);
    Node *newNode=(Node*)malloc(sizeof(Node));
    newNode->team=newTeam;
    newNode->next=NULL;
    if(*list!=NULL)
        newNode->next=*list;   
    *list=newNode;
}

Node *createList(FILE *input,int *numberOfTeams)
{
    Node *list=NULL;
    fscanf(input,"%d",numberOfTeams);
    for(int i=0;i<*numberOfTeams;i++)
        addTeam(input,&list);
    return list;
}

void teamPoints(Team *team)
{
    float points=0;
    for(int i=0;i<team->numberOfPlayers;i++)
        points+=team->player[i].points;
    team->points=points/team->numberOfPlayers;
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

void deleteTeamData(Node **list)
{
    if((*list)==NULL)
        return;
    free((*list)->team->name);
    for(int i=0;i<(*list)->team->numberOfPlayers;i++)
    {
        free((*list)->team->player[i].firstName);
        free((*list)->team->player[i].secondName);
    }
    free((*list));
}

void deleteTeam(Node **list,float minPoints)
{
    if(*list==NULL) 
        return;
    Node *temp=*list;
    if (temp->team->points==minPoints)
    {
        *list=(*list)->next;
        deleteTeamData(&temp);
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
            deleteTeamData(&temp);
            return;
        }
    }
}

void deleteList(Node **list)
{
    Node *temp;
    while((*list)->next!=NULL)
    {
        temp=(*list)->next;
        deleteTeamData(list);
        *list=temp;
    }
    free(*list);
    (*list)=NULL;
}