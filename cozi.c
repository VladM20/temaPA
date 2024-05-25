#include "definitii.h"

Queue *createQueue()
{
    Queue *q=(Queue*)malloc(sizeof(Queue));
    if(q==NULL) 
        return NULL;
    q->front=q->rear=NULL;
    return q;
}

void enQueue(Queue *q,Team left,Team right)
{
    Match *newMatch=(Match*)malloc(sizeof(Match));
    if(q->rear==NULL)
        q->rear=newMatch;
    else
    {
        (q->rear)->next=newMatch;
        (q->rear)=newMatch;
    }
    if(q->front==NULL) 
        q->front=q->rear;
}

Match deQueue(Queue *q)
{
    Match *temp;

}

int isEmpty(Queue *q)
{
    return (q->front==NULL);
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
}