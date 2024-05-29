#include "definitii.h"

TreeNode *newNode(Team *team)
{
    TreeNode *node=(TreeNode*)malloc(sizeof(TreeNode));
    if(!allocWorked(node,"newNode(node)"))
        return NULL;
    
    node->team=(Team*)malloc(sizeof(Team));
    if(!allocWorked(node->team,"newNode(node->team)"))
        return NULL;

    copyTeam(team,node->team);
    node->left=node->right=NULL;
    return node;
}

TreeNode *insert(TreeNode *node,Team *team)
{
    if(node==NULL)
        return newNode(team);
    
    if(team->points<node->team->points)
        node->left=insert(node->left,team);

    else if(team->points>node->team->points)
            node->right=insert(node->right,team);
    
         else
         {
                int deciding=strcmp(team->name,node->team->name);
                if(deciding>0)
                    node->right=insert(node->right,team);
                else 
                    node->left=insert(node->left,team);
         }
    return node;
}