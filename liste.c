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
/*
void copyTeam(Team *source,Team **destination)
{
    Team *newTeam=(Team*)malloc(sizeof(Team));
    if(!allocWorked(newTeam,"copyTeam"))
        return;

    newTeam->name=(char*)malloc((strlen(source->name)+1)*sizeof(char));
    if(!allocWorked(newTeam->name,"copyTeam(newTeam->name)"))
        return;
    strcpy(newTeam->name,source->name);

    newTeam->numberOfPlayers=source->numberOfPlayers;
    newTeam->points=source->points;

    newTeam->player=(Player*)malloc(newTeam->numberOfPlayers*sizeof(Player));
    if(!allocWorked(newTeam->player,"copyTeam(newTeam->player)"))
        return;
    
    for(int i=0;i<newTeam->numberOfPlayers;i++)
    {
        newTeam->player[i].firstName=(char*)malloc((strlen(source->player[i].firstName)+1)*sizeof(char));
        if(!allocWorked(newTeam->player[i].firstName,"copyTeam(newTeam->player[i].firstName)"))
            return;
        strcpy(newTeam->player[i].firstName,source->player[i].firstName);
        
        newTeam->player[i].secondName=(char*)malloc((strlen(source->player[i].secondName)+1)*sizeof(char));
        if(!allocWorked(newTeam->player[i].secondName,"copyTeam(newTeam->player[i].secondName)"))
            return;
        strcpy(newTeam->player[i].secondName,source->player[i].secondName);
        
        newTeam->player[i].points=source->player[i].points;
    }
    *destination=newTeam;
    printf("\n_%s_\n",(*destination)->name);
}
*/
void copyTeam(Team *source, Team *destination) 
{
    if(source==NULL || destination==NULL)
        return;
        
    destination->name=(char*)malloc((strlen(source->name)+1)*sizeof(char));
    if(!allocWorked(destination->name,"copyTeam(destination->name)"))
        return;
    strcpy(destination->name,source->name);

    destination->numberOfPlayers=source->numberOfPlayers;
    destination->points=source->points;

    destination->player=(Player*)malloc(destination->numberOfPlayers*sizeof(Player));
    if(!allocWorked(destination->player,"copyTeam(destination->player)"))
    {
        free(destination->name);
        return;
    }

    for (int i=0;i<destination->numberOfPlayers;i++) 
    {
        destination->player[i].firstName=(char*)malloc((strlen(source->player[i].firstName)+1)*sizeof(char));
        if(!allocWorked(destination->player[i].firstName,"copyTeam(destination->player[i].firstName)"))
        {
            for (int j=0;j<i;j++) 
                free(destination->player[j].firstName);
            free(destination->player);
            free(destination->name);
            return;
        }
        strcpy(destination->player[i].firstName,source->player[i].firstName);

        destination->player[i].secondName=(char*)malloc((strlen(source->player[i].secondName)+1)*sizeof(char));
        if(!allocWorked(destination->player[i].secondName,"copyTeam(destination->player[i].secondName)"))
        {
            for (int j=0;j<i;j++) 
            {
                free(destination->player[j].firstName);
                free(destination->player[j].secondName);
            }
            free(destination->player);
            free(destination->name);
            return;
        }
        strcpy(destination->player[i].secondName,source->player[i].secondName);

        destination->player[i].points=source->player[i].points;
    }
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

void deleteTeam(Team **team)
{
    if(*team==NULL)
        return;
    if((*team)->player!=NULL)
    {
        for(int i=0;i<(*team)->numberOfPlayers;i++)
        {
            free((*team)->player[i].firstName);
            free((*team)->player[i].secondName);
        }
        free((*team)->player);
    }
    if((*team)->name!=NULL)
        free((*team)->name);
    
    free((*team));
    *team=NULL;
}

void deleteTeamData(Node **list)
{
    if((*list)==NULL || (*list)->team==NULL)
        return;
    deleteTeam(&((*list)->team));
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
    if(*list==NULL)
        return;

    Node *temp;
    while((*list)->next!=NULL)
    {
        temp=(*list)->next;
        deleteTeamData(list);
        *list=temp;
    }
    if((*list)->next==NULL)
        deleteTeamData(list);
    free(*list);
    (*list)=NULL;
}

void duplicateList(Node *source,Node **destination)
{
    if(source==NULL)
        return;

    Node *current=source,*end=NULL;
    *destination=NULL;

    while(current!=NULL)
    {
        Node *newNode=(Node*)malloc(sizeof(Node));
        if(!allocWorked(newNode,"duplicateList(newNode)"))
            return;
        
        newNode->team=(Team*)malloc(sizeof(Team));
        if(!allocWorked(newNode->team,"duplicateList(newNode->team)"))
            return;

        copyTeam(current->team,newNode->team);
        newNode->next=NULL;

        if(*destination==NULL)
        {
            *destination=newNode;
            end=newNode;
        }
        else
        {
            end->next=newNode;
            end=newNode;
        }
        current=current->next;
    }
}