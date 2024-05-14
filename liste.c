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
    printf("\n%d ",newTeam->numberOfPlayers);
    newTeam->teamName=(char*)malloc(MAX_LENGTH*sizeof(char));
    readTeamName(input,newTeam->teamName,MAX_LENGTH);
    printf("%s\n",newTeam->teamName);
    for(int i=0;i<newTeam->numberOfPlayers;i++)
    {
        newTeam->player[i].firstName=(char*)malloc(MAX_LENGTH*sizeof(char));
        newTeam->player[i].secondName=(char*)malloc(MAX_LENGTH*sizeof(char));
        fscanf(input,"%s %s %d\n",newTeam->player[i].firstName,newTeam->player[i].secondName,&newTeam->player[i].points);
        //printf("%s %s %d\n",newTeam->player[i].firstName,newTeam->player[i].secondName,newTeam->player[i].points);
    }
    fscanf(input,"\n");
    teamPoints(newTeam);
    newTeam->next=*teams;
    *teams=newTeam;
}

Team *createList(FILE *input)
{
    Team *teams=(Team*)malloc(sizeof(Team));
    teams->next=NULL;
    int numberOfTeams;
    fscanf(input,"%d",&numberOfTeams);
    printf("%d\n",numberOfTeams);
    for(int i=0;i<numberOfTeams;i++)
        addTeam(input,&teams);
    return teams;
}

void teamPoints(Team *team)
{
    float points=0;
    for(int i=0;i<team->numberOfPlayers;i++)
        points+=team->player[i].points;
    team->teamPoints=points/team->numberOfPlayers;
    printf("Punctaj:%.2f\n",team->teamPoints);
}