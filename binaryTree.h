/*Just a basic linked list with tail pointer*/
#include "job.h"
/*Struct definition*/
#ifndef cs537_JobTreeNode
#define cs537_JobTreeNode
typedef struct JobTreeNode /*Tag for the struct*/
{ 
    JobP job;
    struct JobTreeNode * left;
    struct JobTreeNode * right;
}JobTreeNode;/*Actual struct name*/
typedef struct JobTreeNode* JobTreeNodeP;
#endif

JobTreeNodeP create_jobTree();

void insert_JobTree(JobTreeNodeP*, JobP);

JobP get_NextJob(JobTreeNodeP*);

void print_Tree(JobTreeNodeP);
 
