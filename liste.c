#include "definitii.h"

int readTeamName(FILE *input,char *dest,int length)
{
    char c=' ';
    int i;
    for(i=0;i<length && c!='\n' && c!=EOF;i++)
    {
        c=fgetc(input);
        if(c=='\n')
            break;
        if(c==EOF)
        {
            dest[i]='\0';
            return 1;
        }
        dest[i]=c;
    }
    dest[i-1]='\0';
    return 0;
}

void addTeam(FILE *input,List **list)
{
    Team *newTeam=(Team*)malloc(sizeof(Team));
    fscanf(input,"%d ",&newTeam->numberOfPlayers);
    newTeam->name=(char*)malloc(MAX_LENGTH*sizeof(char));
    readTeamName(input,newTeam->name,MAX_LENGTH);
    for(int i=0;i<newTeam->numberOfPlayers;i++)
    {
        newTeam->player[i].firstName=(char*)malloc(MAX_LENGTH*sizeof(char));
        newTeam->player[i].secondName=(char*)malloc(MAX_LENGTH*sizeof(char));
        fscanf(input,"%s %s %d\n",newTeam->player[i].firstName,newTeam->player[i].secondName,&newTeam->player[i].points);
    }
    fscanf(input,"\n");
    teamPoints(newTeam);
    (*list)->team=newTeam;
}

List *createList(FILE *input,int *numberOfTeams)
{
    List *list=NULL,*temp;
    fscanf(input,"%d",numberOfTeams);
    for(int i=0;i<*numberOfTeams;i++)
    {
        temp=(List*)malloc(sizeof(List));
        temp->next=NULL;
        addTeam(input,&temp);
        temp->next=list;
        list=temp;
    }
    return list;
}

void teamPoints(Team *team)
{
    float points=0;
    for(int i=0;i<team->numberOfPlayers;i++)
        points+=team->player[i].points;
    team->points=points/team->numberOfPlayers;
}

float minPoints(List *list,int numberOfTeams)
{
    List *temp=list;
    float min=list->team->points;
    for(int i=0;i<numberOfTeams && temp!=NULL;i++)
    {
        if(min>temp->team->points)
            min=temp->team->points;
        temp=temp->next;
    }
    return min;
}

void deleteTeamData(List **list)
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

void deleteTeam(List **list,float minPoints)
{
    if(*list==NULL) 
        return;
    List *temp=*list;
    if (temp->team->points==minPoints)
    {
        *list=(*list)->next;
        deleteTeamData(&temp);
        return;
    }
    List* prev=*list;
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

void deleteList(List **list)
{
    List *temp;
    while((*list)->next!=NULL)
    {
        temp=(*list)->next;
        deleteTeamData(list);
        *list=temp;
    }
    (*list)=NULL;
}