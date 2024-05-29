#include "definitii.h"

int max(int x,int y)
{
    if(x>y)
        return x;
    else 
        return y;
}

int height(AVLNode *node)
{
    if(node==NULL)
        return -1;
    return node->height;
}

int NodeBalance(AVLNode *node)
{
    if(node==NULL)
        return 0;
    return height(node->left)-height(node->right);
}

AVLNode *newAVLNode(Team *team)
{
    AVLNode *newNode=(AVLNode*)malloc(sizeof(AVLNode));
    if(!allocWorked(newNode,"newAVLNode(node)"))
        return NULL;
    newNode->team=team;
    newNode->height=0;
    newNode->left=newNode->right=NULL;
    return newNode;
}

AVLNode *leftRotation(AVLNode *z)
{
    AVLNode *y=z->right;
    AVLNode *T2=y->left;
    y->left=z;
    z->right=T2;
    z->height=1+max(height(z->left),height(z->right));
    y->height=1+max(height(y->left),height(y->right));
    return y;
}

AVLNode *rightRotation(AVLNode *z)
{
    AVLNode *y=z->left;
    AVLNode *T3=y->right;
    y->right=z;
    z->left=T3;
    z->height=1+max(height(z->left),height(z->right));
    y->height=1+max(height(y->left),height(y->right));
    return y;
}

AVLNode *balanceAVL(AVLNode *node,Team *team)
{
    int balance=NodeBalance(node);
    if(balance>1)
    {
        int balanceChild=NodeBalance(node->left);
        if(balanceChild>0)
            return rightRotation(node);
        else 
        {
            node->left=leftRotation(node->left);
            return rightRotation(node);
        }
    }
    if(balance<-1)
    {
        int balanceChild=NodeBalance(node->right);
        if(balanceChild<0)
            return leftRotation(node);
        else 
        {
            node->right=rightRotation(node->right);
            return leftRotation(node);
        }
    }
    return node;
}
/*
AVLNode *balanceAVL(AVLNode *node,Team *team)
{
    int balance=NodeBalance(node);
    if(balance>1)
    {
        if(team->points < node->left->team->points)
            return rightRotation(node);
        if(team->points > node->right->team->points)
        {
            node->left=leftRotation(node->left);
            return rightRotation(node);
        }
        int deciding=strcmp(team->name,node->team->name);
        if(deciding<0)
            return rightRotation(node);
        else 
            return leftRotation(node);
    }
    if(balance<-1)
    {
        if(team->points > node->left->team->points)
            return leftRotation(node);
        if(team->points < node->right->team->points)
        {
            node->right=rightRotation(node->right);
            return leftRotation(node);
        }
        int deciding=strcmp(team->name,node->team->name);
        if(deciding<0)
            return leftRotation(node);
        else 
            return rightRotation(node);
    }
    return node;
}
*/
AVLNode *insertAVL(AVLNode *node,Team *team)
{
    if(node==NULL)
        return newAVLNode(team);
    
    if(team->points > node->team->points)
        node->right=insertAVL(node->right,team);
    else if(team->points < node->team->points)
            node->left=insertAVL(node->left,team);
        else
        {
            int deciding=strcmp(team->name,node->team->name);
            if(deciding>0)
                node->right=insertAVL(node->right,team);
            else 
                node->left=insertAVL(node->left,team);
        }
    node->height=1+max(height(node->left),height(node->right));
    return balanceAVL(node,team);
}

void freeAVLTree(AVLNode *root)
{
    if(root==NULL)
        return;
    freeAVLTree(root->left);
    freeAVLTree(root->right);
    free(root);
}