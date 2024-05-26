#include "definitii.h"
#define NR_CERINTE 5

int allocWorked(void *pointer,char *function)
{
    //printf("DA (%s)\n",function);
    if(pointer==NULL)
    {
        printf("Nu s-a putut aloca memorie in %s\n",function);
        return 0;
    }
    return 1;
}

//Printeaza echipele cu tot cu jucatori pe ecran.
void printTeams(Node *list)
{
    Node *temp=list;
    for(int j=0;temp!=NULL;j++)
    {
        printf("%d %s\n",temp->team->numberOfPlayers,temp->team->name);
        printf("%s %s %.2f\n",temp->team->player[0].firstName,temp->team->player[0].secondName,temp->team->points);
        //for(int i=0;i<list->team->numberOfPlayers;i++)
            //printf("%s %s %d\n",temp->team->player[i].firstName,temp->team->player[i].secondName,temp->team->player[i].points);
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

void playMatch(Team *team1,Team *team2,Node **winners,Node **losers)
{
    if(team1->points<team2->points)    //pierde stanga
    {
        push(winners,team2);
        push(losers,team1);
    }
    else                              //castiga stanga
    {
        push(losers,team2);
        push(winners,team1);
    }
}

void printQ(Queue *q)
{
    if(q==NULL)
        return;
    Match *temp=q->front;
    while(temp!=NULL)
    {
        printf("%s... \n",temp->team1->name);
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
    Node *list=fcreateList(input,&numberOfTeams);   
    fclose(input);

    if(cerinte[1]) 
    {
        int target=powerOf2(numberOfTeams);
        while(numberOfTeams>target)
        {
            deleteLastTeam(&list,minPoints(list,numberOfTeams));
            numberOfTeams--;
        }
    }
    
    if(cerinte[2])
    {
        Queue *q=createQueue(list);
        Node *winners=NULL,*losers=NULL;
        //while(numberOfTeams>8)
        //{
            while(!isEmpty(q))
            {
                Team *team1=NULL,*team2=NULL;
                deQueue(q,&team1,&team2);
                //printf("%s - %s\n",team1->name,team2->name);
                playMatch(team1,team2,&winners,&losers);
            }
            /*deleteList(&losers);    //Stiva are aceeasi structura ca o lista.
            deleteQueue(q);
            q=createQueue(winners);
            deleteList(&winners);
            numberOfTeams/=2;
        }*/
        Node *last8Teams=NULL;
        while(winners!=NULL)
        {
            break;
        }

    }
    
    FILE* output=fopen(argv[3],"wt");
    writeTeams(output,list,numberOfTeams);
    fclose(output);
    deleteList(&list);
    return 0;
}