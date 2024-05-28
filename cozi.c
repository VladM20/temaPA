#include "definitii.h"

int isEmpty(Queue *q)
{
    return (q->front==NULL);
}

Queue *createQueue()
{
    Queue *q=(Queue*)malloc(sizeof(Queue));
    if(!allocWorked(q,"createQueue(q)"))
        return NULL;

    q->front=NULL;
    q->rear=NULL;
    return q;
}

Queue *ListToQueue(Node *list)
{
    if(list==NULL)
        return NULL;
    Queue *q=createQueue();
    Node *temp=list;
    while(temp!=NULL && temp->next!=NULL)
    {
        enQueue(q,temp->team,temp->next->team);
        temp=temp->next->next;
    }
    return q;
}

void enQueue(Queue *q,Team *team1,Team *team2)
{
    if(q==NULL || team1==NULL || team2==NULL)
    {
        printf("Parametrii gresiti in enQueue\n");
        return;
    }

    Match *newMatch=(Match*)malloc(sizeof(Match));
    if(!allocWorked(newMatch,"enQueue(newMatch)"))
        return;

    newMatch->team1=(Team*)malloc(sizeof(Team));
    if(!allocWorked(newMatch->team1,"enQueue(newMatch->team1)"))
        return;
    copyTeam(team1,newMatch->team1);

    newMatch->team2=(Team*)malloc(sizeof(Team));
    if(!allocWorked(newMatch,"enQueue(newMatch->team2)"))
        return;
    copyTeam(team2,newMatch->team2);
    newMatch->next=NULL;

    if(q->rear==NULL)
    {
        q->rear=newMatch;
        q->front=newMatch;
    }
    else
    {
        q->rear->next=newMatch;
        q->rear=newMatch;
    }
}

void deQueue(Queue *q,Team **team1,Team **team2)
{
    if(isEmpty(q))
    {
        *team1=NULL;
        *team2=NULL;
        return;
    }

    Match *temp=q->front;
    q->front=q->front->next;

    *team1=temp->team1;
    *team2=temp->team2;
    /*
    *team1=(Team*)malloc(sizeof(Team));
    if(!allocWorked(team1,"deQueue(team1)"))
        return;
    copyTeam(temp->team1,*team1);

    *team2=(Team*)malloc(sizeof(Team));
    if(!allocWorked(team2,"deQueue(team1)"))
        return;
    copyTeam(temp->team2,*team2);
    */
    if(isEmpty(q))
        q->rear=NULL;
    //freeTeam(temp->team1);
    //freeTeam(temp->team2);
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
        freeTeam((*q)->front->team1);
        freeTeam((*q)->front->team2);
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
    Queue *q=createQueue();
    while(stack!=NULL && stack->next!=NULL)
    {
        Team *team1=pop(&stack);
        if(team1==NULL)
        {
            printf("scandal\n");
            break;
        }

        Team *team2=pop(&stack);
        if(team2->name==NULL)
        {
            printf("scandal2\n");
            break;
        }
        enQueue(q,team1,team2);
    }
    return q;
}