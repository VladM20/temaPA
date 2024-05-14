#include "headers/liste.h"

void printTeam(Team *team)
{
    Team *temp=team;
    printf("%d %s\n",team->numberOfPlayers,team->teamName);
    for(int i=0;i<team->numberOfPlayers && team!=NULL;i++)
    {
        printf("%s %s %d\n",temp->player[i].firstName,temp->player[i].secondName,temp->player[i].points);
        temp=temp->next;
    }
    
}

int main(int argc,char* argv[])
{
    FILE * input=fopen(argv[1],"rt");
    Team *teams=createList(input);
    printTeam(teams);
    fclose(input);
    FILE* out=fopen("r.out","wt");
    fclose(out);
    return 0;
}