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
    Team *teams=(Team*)malloc(sizeof(Team));
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
    float min=0;
    for(int i=0;i<numberOfTeams;i++)
        if(min>teams->teamPoints)
            min=teams->teamPoints;
    return min;
}

void deletePlayers(Team **teams)
{
    for(int i=0;i<(*teams)->numberOfPlayers;i++)
    {
        free((*teams)->player[i].firstName);
        free((*teams)->player[i].secondName);
    }
}

void deleteTeam(Team **teams,float minPoints)
{
    if(*teams==NULL) 
        return;
    Team *temp=*teams;
    if (temp->val==v)
    {
        *teams=(*teams)->next;
        free(temp->teamName);
        free(temp->player->firstName);
        free(temp->player->secondName);
        free(temp);
        return;
    }
    Team* prev=*teams;
    while(temp!=NULL)
    {
        if(temp->val!=v)
        {
            prev=temp;
            temp=temp->next;
        } 
        else 
        {
            prev->next=temp->next;
            free(temp->teamName);
            deletePlayers(temp);
            free(temp);
            return;
        }
    }
}

void deleteList(Team **teams)
{
    Team *temp;
    while(*teams!=NULL)
    {
        temp=(*teams)->next;
        free(teams->player->firstName);
        free(teams->player->secondName);
        free(*teams);
        *teams=temp;
    }
    *teams=NULL;
}