#include "definitii.h"

Queue *createQueue(Node *list)
{
    Queue *q=(Queue*)malloc(sizeof(Queue));
    if(q==NULL) 
        return NULL;
    q->front=q->rear=NULL;
    while(list!=NULL && list->next!=NULL)
    {
        enQueue(q,list->team,(list->next)->team);
        list=(list->next)->next;
    }
    return q;
}

int isEmpty(Queue *q)
{
    return (q->front==NULL);
}

void enQueue(Queue *q,Team *left,Team *right)
{
    Match *newMatch=(Match*)malloc(sizeof(Match));
    newMatch->left=left;
    newMatch->right=right;
    newMatch->next=NULL;
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

void deQueue(Queue *q,Team *left,Team *right)
{
    Match *temp;
    if(isEmpty(q))
        return;
    temp=q->front;
    left=temp->left;
    right=temp->right;
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
}