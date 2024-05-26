#include "definitii.h"

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
    while(length>0 && (name[length-1]==' ' || name[length-1]=='\n'  || name[length-1]=='\r'))
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

Team *initializeTeam(int numberOfPlayers)
{
    Team *newTeam=(Team*)malloc(sizeof(Team));
    if(!allocWorked(newTeam,"initializeTeam(newTeam)"))
        return NULL; 

    newTeam->numberOfPlayers=numberOfPlayers;

    newTeam->name=(char*)malloc(MAX_LENGTH*sizeof(char));
    if(!allocWorked(newTeam->name,"initializeTeam(name)"))
        return NULL;
    
    newTeam->player=initializePlayers(newTeam->numberOfPlayers);
    return newTeam;
}

Player *initializePlayers(int numberOfPlayers)
{
    Player *player=(Player*)malloc(numberOfPlayers*sizeof(Player));
    if(!allocWorked(player,"initializePlayers(player)"))
        return NULL;

    for(int i=0;i<numberOfPlayers;i++)
    {
        player[i].firstName=(char*)malloc(MAX_LENGTH*sizeof(char));
        if(!allocWorked(player[i].firstName,"initializePlayers(firstName)"))
            return NULL;
        player[i].secondName=(char*)malloc(MAX_LENGTH*sizeof(char));
        if(!allocWorked(player[i].secondName,"initializePlayers(secondName)"))
            return NULL;
    }
    return player;
}

void addTeam(FILE *input,Node **list)
{
    Team *newTeam=(Team*)malloc(sizeof(Team));
    if(!allocWorked(newTeam,"addTeam(newTeam)"))
        return; 
    fscanf(input,"%d",&(newTeam->numberOfPlayers));
    fgetc(input);   //scapa de spatiul dintre numarul de jucatori si numele echipei
    newTeam->name=readTeamName(input);
    if(!allocWorked(newTeam->name,"addTeam(name)"))
        return;

    newTeam->player=(Player*)malloc(newTeam->numberOfPlayers*sizeof(Player));
    if(!allocWorked(newTeam->player,"addTeam(newTeam->player)"))
        return;


    for(int i=0;i<newTeam->numberOfPlayers;i++)
    {
        newTeam->player[i].firstName=readName(input);
        newTeam->player[i].secondName=readName(input);
        fscanf(input,"%d",&(newTeam->player[i].points));
    }
    teamPoints(newTeam);
    Node *newNode=(Node*)malloc(sizeof(Node));
    if(!allocWorked(newNode,"addTeam(newNode)"))
        return;

    newNode->team=newTeam;
    newNode->next=NULL;
    if(*list!=NULL)
        newNode->next=*list;   
    *list=newNode;
}

void copyTeam(Team *source,Team **destination)
{
    Team *temp=(Team*)malloc(sizeof(Team));
    if(!allocWorked(temp,"copyTeam"))
        return;
    
    strcpy(temp->name,source->name);
    temp->numberOfPlayers=source->numberOfPlayers;
    temp->points=source->points;
    for(int i=0;i<temp->numberOfPlayers;i++)
    {
        strcpy(temp->player[i].firstName,source->player[i].firstName);
        strcpy(temp->player[i].secondName,source->player[i].secondName);
        temp->player[i].points=source->player[i].points;
    }
    *destination=temp;
}

Node *createList(int numberOfTeams)
{
    Node *list=NULL;
    for(int i=0;i<numberOfTeams;i++)
    {

    }    
    return list;
}

Node *fcreateList(FILE *input,int *numberOfTeams)
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

void deleteLastTeam(Node **list,float minPoints)
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

Node *duplicateList(Node *source)
{
    Node *destination=NULL;
    while(source!=NULL)
    {
        break;   
    }
    return NULL;
}