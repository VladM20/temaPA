#include "definitii.h"
#define NR_CERINTE 5

//Printeaza echipele cu tot cu jucatori pe ecran.
void printTeams(Node *list,int numberOfTeams)
{
    Node *temp=list;
    for(int j=0;j<numberOfTeams && temp!=NULL;j++)
    {
        printf("%d %s\n",temp->team->numberOfPlayers,temp->team->name);
        for(int i=0;i<list->team->numberOfPlayers;i++)
            printf("%s %s %d\n",temp->team->player[i].firstName,temp->team->player[i].secondName,temp->team->player[i].points);
        temp=temp->next;
        printf("\n");
    }
}
//Scrie echipele in fisier.
void writeTeams(FILE* output,Node *list,int numberOfTeams)
{
    Node *temp=list;
    for(int j=0;j<numberOfTeams && temp!=NULL;j++)
    {
        fprintf(output,"%s\n",temp->team->name);
        //printf("%d.%s (%d)\n",j,temp->team->name,strlen(temp->team->name));
        temp=temp->next;
    }
}
//Gaseste cea mai mare putere a lui 2 mai mica decat n. 
int powerOf2(int n)
{
    if(n<1)
        return 0;
    int rezultat=1;
    for(int i=0;i<8*sizeof(int);i++)    //i merge pana la numarul de biti al n
    {
        int incercare=1<<i;             //incercam fiecare putere a lui 2
        if(incercare>n)
            break;
        rezultat=incercare;
    }
    return rezultat;
}

void playMatch(Team *left,Team *right,Node **winners,Node **losers)
{
    if(left->points<right->points)    //pierde stanga
    {
        push(winners,right);
        push(losers,left);
    }
    else                              //castiga stanga
    {
        push(losers,right);
        push(winners,left);
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
    Node *list=createList(input,&numberOfTeams);   
    fclose(input);

    if(cerinte[1]) 
    {
        int target=powerOf2(numberOfTeams);
        while(numberOfTeams>target)
        {
            deleteTeam(&list,minPoints(list,numberOfTeams));
            numberOfTeams--;
        }
    }
    /*
    if(cerinte[2])
    {
        Queue *q=createQueue(list);
        Node *winners=NULL,*losers=NULL;
        while(q!=NULL)
        {
            Team *left=NULL,*right=NULL;
            deQueue(q,left,right);
            playMatch(left,right,&winners,&losers);
        }
    }
    */
    FILE* output=fopen(argv[3],"wt");
    writeTeams(output,list,numberOfTeams);
    fclose(output);
    deleteList(&list);
    return 0;
}