#include "definitii.h"

Queue *createQueue(Node *list)
{
    if(list==NULL)
        return NULL;
    Queue *q=(Queue*)malloc(sizeof(Queue));
    if(!allocWorked(q,"createQueue"))
        return NULL;
    q->front=NULL;
    q->rear=NULL;

    Node *temp=list;
    while(temp!=NULL && temp->next!=NULL)
    {
        enQueue(q,temp->team,temp->next->team);
        temp=temp->next->next;
    }
    return q;
}

int isEmpty(Queue *q)
{
    return (q->front==NULL);
}

void enQueue(Queue *q,Team *team1,Team *team2)
{
    Match *newMatch=(Match*)malloc(sizeof(Match));
    if(!allocWorked(newMatch,"enQueue(newMatch)"))
        return;

    newMatch->team1=(Team*)malloc(sizeof(Team));
    if(!allocWorked(newMatch->team1,"enQueue(newMatch->team1)"))
        return;

    newMatch->team2=(Team*)malloc(sizeof(Team));
    if(!allocWorked(newMatch,"enQueue(newMatch->team2)"))
        return;

    copyTeam(team1,newMatch->team1);
    copyTeam(team2,newMatch->team2);
    newMatch->next=NULL;

    if(q->rear==NULL)
    {
        q->rear=newMatch;
        q->front=newMatch;
    }
    else
    {
        (q->rear)->next=newMatch;
        q->rear=newMatch;
    }
}

void deQueue(Queue *q,Team **team1,Team **team2)
{
    Match *temp=NULL;
    if(isEmpty(q))
        return;

    temp=q->front;
    q->front=(q->front)->next;

    *team1=(Team*)malloc(sizeof(Team));
    if(!allocWorked(team1,"deQueue(team1)"))
        return;
    copyTeam(temp->team1,*team1);

    *team2=(Team*)malloc(sizeof(Team));
    if(!allocWorked(team2,"deQueue(team1)"))
        return;
    copyTeam(temp->team2,*team2);
    
    if(isEmpty(q))
        q->rear=NULL;
    free(temp);
}

void deleteQueue(Queue **q)
{
    if(*q==NULL)
        return;
    
    Match *nextMatch;
    while(!isEmpty(*q))
    {
        nextMatch=(*q)->front->next;
        deleteTeam(&(*q)->front->team1);
        deleteTeam(&(*q)->front->team2);
        free((*q)->front);
        (*q)->front=nextMatch;
    }
    free(*q);
    *q=NULL;
}

Queue *queueFromStack(Node *stack)
{
    if(stack==NULL)
    {
        printf("\nSTIVA GOALA\n");
        return NULL;
    }

    Queue *q=(Queue*)malloc(sizeof(Queue));
    if(!allocWorked(q,"queueFromStack(q)"))
        return NULL;
    
    q->front=NULL;
    q->rear=NULL;

    while(stack!=NULL && stack->next!=NULL)
    {
        Team *team1=pop(&stack);
        if(team1==NULL)
        {
            printf("scandal\n");
            break;
        }
        if(team1->name==NULL)
            break;
        //printf("team1: %s\n",team1.name);
        Team *team2=pop(&stack);
        if(team2->name==NULL)
            break;
        //printf("team2: %s\n",team2.name);
        /*
        Team *newTeam1=(Team*)malloc(sizeof(Team));
        if(!allocWorked(newTeam1,"queueFromStack(newTeam1)"))
            return NULL;

        Team *newTeam2=(Team*)malloc(sizeof(Team));
        if(!allocWorked(newTeam2,"queueFromStack(newTeam2)"))
            return NULL;
        
        copyTeam(&team1,newTeam1);
        copyTeam(&team2,newTeam2);
        */
        enQueue(q,team1,team2);
    }
    return q;
}