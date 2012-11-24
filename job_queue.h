/*Just a basic linked list with tail pointer*/
#include "job.h"
/*Struct definition*/
#ifndef cs537_JobNode
#define cs537_JobNode
struct JobNode /*Tag for the struct*/
{ 
    Job job;
    struct JobNode * next;
};/*Actual struct name*/
typedef struct JobNode* JobNode;
#endif
/*Define our job queue, but not twice*/
#ifndef cs537_JobQueue
#define cs537_JobQueue
typedef struct cs537_JobQueue /*Tag for the struct*/
{ 
    JobNode head;
    JobNode tail;
    int size;
}*JobQueue;/*Actual struct name*/
#endif

JobQueue create_JobQueue();

void destory_JobQueue(JobQueue);

void push_JobQueue(JobQueue, Job);

Job pop_JobQueue(JobQueue);

