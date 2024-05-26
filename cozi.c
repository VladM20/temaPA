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
        //printf("Meci: %s (1)\n%s (2)\n",temp->team->name,temp->next->team->name);
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
    if(!allocWorked(newMatch,"enQueue"))
        return;
    newMatch->team1=team1;
    newMatch->team2=team2;
    newMatch->next=NULL;

    if(q->rear==NULL)
        q->rear=q->front=newMatch;
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
    *team1=temp->team1;
    *team2=temp->team2;
    q->front=(q->front)->next;
    if(isEmpty(q))
        q->rear=NULL;
    free(temp);
}

void deleteQueue(Queue *q)
{
    Match *temp;
    while(!isEmpty(q))
    {
        temp=q->front;
        q->front=q->front->next;
        
        free(temp);
    }
    free(q);
    q=NULL;
}