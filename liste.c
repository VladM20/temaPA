#include "headers/input.h"
#include "headers/liste.h"

Team *createTeam()
{
    Team *teams=(Team*)malloc(sizeof(Team));
    teams->next=NULL;
    teams->numberOfPlayers=0;
    teams->members=NULL;
    return teams;
}

void readTeamName(FILE *input,char *dest,int n)
{
    char c;
    for(int i=0;i<n;i++)
    {
        c=fgetc(input);
        if(c=='\n')
            break;
        dest[i]=c;
    }
    dest[n]='\0';
}

Team *readTeam(FILE *input)
{
    Team *team=(Team*)malloc(sizeof(Team));
    fscanf(input,"%d ",&team->numberOfPlayers);
    for(int i=0;i<team->numberOfPlayers;i++)
    {
        
    }
    return team;
}

void addMembers(Member *source,Member *destination)
{
    while(source!=NULL)
    {
        strcpy(destination->player.firstName,source->player.secondName);
        strcpy(destination->player.secondName,source->player.secondName);
        destination->player.points=source->player.points;
        source=source->next;
        destination=destination->next;
    }
}

void addTeam(Team **teams,Team *t)
{
    Team *newTeam=(Team*)malloc(sizeof(Team));
    newTeam->next=*teams;
    newTeam->numberOfPlayers=t->numberOfPlayers;
    strcpy(newTeam->teamName,t->teamName);
    Member *source=t->members;
    Member *destination=newTeam->members;
    for(int i=0;i<t->numberOfPlayers && source!=NULL;i++)
    {
        strcpy(newTeam->members->player.firstName,source->player.firstName);
        strcpy(newTeam->members->player.secondName,source->player.secondName);
        newTeam->members->player.points=source->player.points;
        source=source->next;
    }
}