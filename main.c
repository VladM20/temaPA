#include "definitii.h"
#define NR_CERINTE 5

int allocWorked(void *pointer,char *function)
{
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
    //printf("%s[%.2f]---%s[%.2f]\n",team1->name,team1->points,team2->name,team2->points);
    if(team1->points==team2->points)    //pierde team1, castiga team2
    {
        team2->points++;
        push(winners,team2);
        push(losers,team1);
        return;
    }
    if(team1->points<team2->points)    //pierde team1, castiga team2
    {
        team2->points++;
        push(winners,team2);
        push(losers,team1);
        return;
    }
    else                              //castiga team1, pierde team2
    {
        team1->points++;
        push(losers,team2);
        push(winners,team1);
        return;
    }
}

void printQ(Queue *q)
{
    if(q==NULL)
    {
        printf("\n...E GOALA COADA...\n");
        return;
    }
    Match *temp=q->front;
    while(temp!=NULL)
    {
        if(temp->team1==NULL || temp->team2==NULL)
            printf("ERROR\n");
        if(temp->team2->name==NULL)
            printf("Team 2 e de vina\n");
        printf("...%s...%s... \n",temp->team1->name,temp->team2->name);
        temp=temp->next;
    }
}

void addSpaces(FILE *output,int numberOfSpaces)
{
    while(numberOfSpaces)
    {
        fprintf(output," ");
        numberOfSpaces--;
    }
}

void writeRoundHeader(FILE *output,int roundNumber)
{
    fprintf(output,"\n--- ROUND NO:%d\n",roundNumber);
}

void writeRound(FILE *output,Team *team1,Team *team2)
{
    int leftSpaces,rightSpaces;
    leftSpaces=ROUND_PADDING-strlen(team1->name);
    fprintf(output,"%s",team1->name);
    addSpaces(output,leftSpaces);
    fprintf(output,"-");
    rightSpaces=ROUND_PADDING-strlen(team2->name);
    addSpaces(output,rightSpaces);
    fprintf(output,"%s\n",team2->name);
}

void writeWinners(FILE* output,Node *stack,int roundNumber)
{
    fprintf(output,"\nWINNERS OF ROUND NO:%d\n",roundNumber);
    Node *temp=stack;
    while(temp!=NULL)
    {
        fprintf(output,"%s",temp->team->name);
        addSpaces(output,WINNER_PADDING-strlen(temp->team->name));
        fprintf(output,"-  %4.2f\n",temp->team->points);
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

    FILE* output=fopen(argv[3],"wt");

    if(cerinte[1])  //task 2
    {
        int target=powerOf2(numberOfTeams);
        while(numberOfTeams>target)
        {
            deleteLastTeam(&list,minPoints(list,numberOfTeams));
            numberOfTeams--;
        }
    }
    writeTeams(output,list,numberOfTeams);  //task 1

    if(cerinte[2])  //task 3
    {
        Queue *q=createQueue(list);
        Node *winners=NULL,*losers=NULL;
        Node *last8Teams=NULL;
        int round=0;
        while(numberOfTeams>1)
        {
            round++;
            writeRoundHeader(output,round);
            while(!isEmpty(q))
            {
                Team *team1=NULL,*team2=NULL;
                deQueue(q,&team1,&team2);
                writeRound(output,team1,team2);
                playMatch(team1,team2,&winners,&losers);
            }
            writeWinners(output,winners,round);
            deleteList(&losers);    //Stiva are aceeasi structura ca o lista.
            numberOfTeams/=2;
            if(numberOfTeams==1)
                break;
            if(numberOfTeams==8)
                duplicateList(winners,&last8Teams);
            deleteQueue(&q);
            q=queueFromStack(winners);
            winners=NULL;
        }
        //printTeams(last8Teams);
    }
    
    
    fclose(output);
    deleteList(&list);
    return 0;
}