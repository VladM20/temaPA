#include "headers/liste.h"

int readTeamName(FILE *input,char *dest,int length)
{
    char c=' ';
    for(int i=0;i<length && c!='\n' && c!=EOF;i++)
    {
        c=fgetc(input);
        if(c=='\n')
            break;
        if(c==EOF)
        {
            dest[length]='\0';
            return 1;
        }
        dest[i]=c;
    }
    dest[length]='\0';
    return 0;
}

void readMember(FILE *input,Member **member)
{
    Member *newMember=(Member*)malloc(sizeof(Member));
    newMember->next=*member;
    fscanf(input,"%s %s %d\n",newMember->player.firstName,newMember->player.secondName,newMember->player.points);
    member=newMember;
}

Team *readTeam(FILE *input)
{
    Team *team=(Team*)malloc(sizeof(Team));
    fscanf(input,"%d ",&team->numberOfPlayers);
    readTeamName(input,team->teamName,MAX_LENGTH);
    for(int i=0;i<team->numberOfPlayers;i++)
    {
        
    }
    return team;
}