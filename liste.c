#include "headers/liste.h"

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

void addTeam(FILE *input,Team **teams)
{
    Team *newTeam=(Team*)malloc(sizeof(Team));
    fscanf(input,"%d ",&newTeam->numberOfPlayers);
    newTeam->teamName=(char*)malloc(MAX_LENGTH*sizeof(char));
    readTeamName(input,newTeam->teamName,MAX_LENGTH);
    for(int i=0;i<newTeam->numberOfPlayers;i++)
    {
        newTeam->player[i].firstName=(char*)malloc(MAX_LENGTH*sizeof(char));
        newTeam->player[i].secondName=(char*)malloc(MAX_LENGTH*sizeof(char));
        fscanf(input,"%s %s %d\n",newTeam->player[i].firstName,newTeam->player[i].secondName,&newTeam->player[i].points);
    }
    fscanf(input,"\n");
    teamPoints(newTeam);
    newTeam->next=*teams;
    *teams=newTeam;
}

Team *createList(FILE *input,int *numberOfTeams)
{
    Team *teams;
    teams->next=NULL;
    fscanf(input,"%d",numberOfTeams);
    for(int i=0;i<*numberOfTeams;i++)
        addTeam(input,&teams);
    return teams;
}

void teamPoints(Team *team)
{
    float points=0;
    for(int i=0;i<team->numberOfPlayers;i++)
        points+=team->player[i].points;
    team->teamPoints=points/team->numberOfPlayers;
}

float minPoints(Team *teams,int numberOfTeams)
{
    Team *temp=teams;
    float min=teams->teamPoints;
    for(int i=0;i<numberOfTeams && temp!=NULL;i++)
    {
        if(min>temp->teamPoints)
            min=temp->teamPoints;
        temp=temp->next;
    }
    return min;
}

void deleteTeamData(Team **team)
{
    if((*team)==NULL)
        return;
    free((*team)->teamName);
    for(int i=0;i<(*team)->numberOfPlayers;i++)
    {
        free((*team)->player[i].firstName);
        free((*team)->player[i].secondName);
    }
    free((*team));
}

void deleteTeam(Team **teams,float minPoints)
{
    if(*teams==NULL) 
        return;
    Team *temp=*teams;
    if (temp->teamPoints==minPoints)
    {
        *teams=(*teams)->next;
        deleteTeamData(&temp);
        return;
    }
    Team* prev=*teams;
    while(temp!=NULL)
    {
        if(temp->teamPoints!=minPoints)
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

void deleteList(Team **teams)
{
    Team *temp;
    while((*teams)->next!=NULL)
    {
        temp=(*teams)->next;
        deleteTeamData(teams);
        *teams=temp;
    }
    (*teams)=NULL;
}