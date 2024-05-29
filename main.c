#include "definitii.h"
#define NR_CERINTE 5

//Printeaza echipele cu tot cu jucatori pe ecran. (Utila pentru debugging)
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
//Printeaza coada Q pe ecran. (Utila pentru debugging)
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
            printf("Coada are echipe lipsa\n");
        printf("...%s...%s... \n",temp->team1->name,temp->team2->name);
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

    int numberOfTeams=0;
    FILE *input=fopen(argv[2],"rt");
    Node *list=createList(input,&numberOfTeams);
    fclose(input);
    FILE* output=fopen(argv[3],"wt");

    if(cerinte[1])  //task 2
        task2(&numberOfTeams,&list);
    writeTeams(output,list,numberOfTeams);  //task 1

    Node *last8Teams=NULL;
    if(cerinte[2])  //task 3
        task3(output,&numberOfTeams,&list,&last8Teams);

    if(cerinte[3])  //task 4
        task4(output,&last8Teams);
    fclose(output);
    deleteList(&list);
    return 0;
}