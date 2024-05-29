#include "definitii.h"

void writeTeams(FILE* output,Node *list,int numberOfTeams)
{
    Node *temp=list;
    for(int j=0;j<numberOfTeams && temp!=NULL;j++)
    {
        fprintf(output,"%s\n",temp->team->name);
        temp=temp->next;
    }
}

void playMatch(Team *team1,Team *team2,Node **winners,Node **losers)
{
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

void writeMatch(FILE *output,Team *team1,Team *team2)
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
        fprintf(output,"-  %.2f\n",temp->team->points);
        temp=temp->next;
    }
}

void task2(int *numberOfTeams,Node **list)
{
    int target=powerOf2(*numberOfTeams);
    while(*numberOfTeams>target)
    {
        deleteLastTeam(list,minPoints(*list,*numberOfTeams));
        (*numberOfTeams)--;
    }
}

void task3(FILE *output,int *numberOfTeams,Node **list,Node **last8Teams)
{
    Queue *q=ListToQueue(*list);
    Node *winners=NULL,*losers=NULL;
    int round=0;
    while(*numberOfTeams>1)
    {
        round++;
        writeRoundHeader(output,round);
        while(!isEmpty(q))
        {
            Team *team1=NULL,*team2=NULL;
            deQueue(q,&team1,&team2);
            if(team1==NULL || team2==NULL)
            {
                printf("Eroare masiva\n");
                exit(25);
            }
            writeMatch(output,team1,team2);
            playMatch(team1,team2,&winners,&losers);
        }
        writeWinners(output,winners,round);
        deleteStack(&losers);
        *numberOfTeams/=2;
        if(*numberOfTeams==8)
            *last8Teams=copyList(winners);
        deleteQueue(&q);
        if(*numberOfTeams==1)
            break;
        q=queueFromStack(winners);
        winners=NULL;
    }
}

void writeBST(FILE *output,TreeNode *root)
{
    if(root==NULL)
        return;
    
    writeBST(output,root->right);
    fprintf(output,"%s",root->team->name);
    addSpaces(output,WINNER_PADDING-strlen(root->team->name));
    fprintf(output,"-  %.2f\n",root->team->points);
    writeBST(output,root->left);
}

void BSTToList(TreeNode *root,Node **list)
{
    if(root==NULL)
        return;

    BSTToList(root->right,list);
    listAddToEnd(root->team,list);
    BSTToList(root->left,list);
}

void task4(FILE *output,Node *last8Teams,Node **orderedTeams)
{
    fprintf(output,"\nTOP 8 TEAMS:\n");
    TreeNode *root=NULL;
    Node *temp=last8Teams;
    while(temp!=NULL)
    {
        root=insert(root,temp->team);
        temp=temp->next;
    }
    *orderedTeams=NULL;
    BSTToList(root,orderedTeams);
    writeBST(output,root);
    freeTree(root);
}

void writeAVL(FILE *output,AVLNode *root,int level)
{
    if(root==NULL)
        return;
    if(level==2)
        fprintf(output,"%s\n",root->team->name); 
    writeAVL(output,root->right,level+1);
    writeAVL(output,root->left,level+1);
}

void task5(FILE *output,Node *orderedTeams)
{
    AVLNode *root=NULL;
    Node *temp=orderedTeams;
    while(temp!=NULL)
    {
        root=insertAVL(root,temp->team);
        temp=temp->next;
    }
    fprintf(output,"\nTHE LEVEL 2 TEAMS ARE: \n");
    writeAVL(output,root,0);
    freeAVLTree(root);
}