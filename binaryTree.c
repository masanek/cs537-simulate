#include "binaryTree.h"

#include<stdlib.h>
#include<stdio.h>

JobTreeNodeP create_jobTree()
{
    return NULL;
}

void insert_JobTree(JobTreeNodeP* tree, JobP toAdd)
{
    if((*tree) == NULL)
    {
        (*tree) = (JobTreeNodeP)malloc(sizeof(JobTreeNode));
        (*tree)->job = toAdd;
        (*tree)->left = NULL;
        (*tree)->right = NULL;
    }
    else
    {
        if((*tree)->job->time_remaining <= toAdd->time_remaining)
        {
            insert_JobTree(&((*tree)->right), toAdd);
        }
        else
        {
            insert_JobTree(&((*tree)->left), toAdd);
        }
    }
}

JobP get_NextJob(JobTreeNodeP* tree)
{
    JobP return_val;
    JobTreeNodeP temp;
    if((*tree) == NULL)
    {
        return NULL;
    }
    if((*tree)->left == NULL)
    {
        return_val = (*tree)->job;
        if((*tree)->right != NULL)
        {
            temp = (*tree)->right;
            free(*tree);
            (*tree) = temp;
        }
        else
        {
            free(*tree);
            (*tree) = NULL;
        }
        return return_val;
    }
    else if((*tree)->left->left == NULL && (*tree)->left->right == NULL)
    {
        return_val = (*tree)->left->job;
        free((*tree)->left);
        (*tree)->left = NULL;
        return return_val;
    }
    else
    {
        return get_NextJob(&((*tree)->left));
    }
}

void print_Tree(JobTreeNodeP tree)
{
   if(tree==NULL)
   {
        return;
   }
   else
   {
        print_Tree(tree->left);
        printf("in Line:%s IO:%f TimeLeft:%i\n",tree->job->cmd_name, tree->job->IOOperations, tree->job->time_remaining);
        print_Tree(tree->right);
   }
}
