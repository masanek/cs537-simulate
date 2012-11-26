/*Just a basic linked list with tail pointer*/
#include "job.h"
/*Struct definition*/
#ifndef cs537_JobNode
#define cs537_JobNode
struct JobNode /*Tag for the struct*/
{ 
    JobP job;
    struct JobNode * next;
};/*Actual struct name*/
typedef struct JobNode* JobNodeP;
#endif
/*Define our job queue, but not twice*/
#ifndef cs537_JobQueue
#define cs537_JobQueue
typedef struct cs537_JobQueue /*Tag for the struct*/
{ 
    JobNodeP head;
    JobNodeP tail;
    int size;
}JobQueue,*JobQueueP;/*Actual struct name*/
#endif

JobQueueP create_JobQueue();

void destory_JobQueue(JobQueueP);

void push_JobQueue(JobQueueP, JobP);

JobP pop_JobQueue(JobQueueP);

int isEmpty_JobQueue(JobQueueP);
