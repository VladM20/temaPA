#include "headers/liste.h"
#define NR_CERINTE 5
//Printeaza echipele cu tot cu jucatori pe ecran.
void printTeams(Team *teams,int numberOfTeams)
{
    Team *temp=teams;
    for(int j=0;j<numberOfTeams && temp!=NULL;j++)
    {
        printf("%d %s\n",temp->numberOfPlayers,temp->teamName);
        for(int i=0;i<teams->numberOfPlayers;i++)
            printf("%s %s %d\n",temp->player[i].firstName,temp->player[i].secondName,temp->player[i].points);
        temp=temp->next;
        printf("\n");
    }
}
//Scrie echipele in fisier.
void writeTeams(FILE* output,Team *teams,int numberOfTeams)
{
    Team *temp=teams;
    for(int j=0;j<numberOfTeams && temp!=NULL;j++)
    {
        fprintf(output,"%s\n",temp->teamName);
        temp=temp->next;
    }
}


int main(int argc,char* argv[])
{
    int cerinte[NR_CERINTE];
    FILE *fisier_cerinte=fopen(argv[1],"rt");
    for(int i=0;i<NR_CERINTE;i++)
        fscanf(fisier_cerinte,"%d",&cerinte[i]);
    fclose(fisier_cerinte);

    FILE *input=fopen(argv[2],"rt");
    int numberOfTeams=0;
    Team *teams=createList(input,&numberOfTeams);
    //printTeams(teams,numberOfTeams);
    fclose(input);
    FILE* output=fopen(argv[3],"wt");
    writeTeams(output,teams,numberOfTeams);
    fclose(output);
    deleteList(&teams);
    return 0;
}