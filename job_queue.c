#include <stdlib.h>
#include <stdio.h>
#include "job_queue.h"

JobQueueP create_JobQueue()
{
    /*Malloc the memory*/
    JobQueueP temp_queue = (JobQueueP)malloc(sizeof(JobQueue));
    /*Not sure if these are necessary*/
    temp_queue->head = NULL;
    temp_queue->tail = NULL;
    temp_queue->size = 0;
    return temp_queue;
}

void destroy_JobQueue(JobQueueP queue)
{
    JobNodeP temp_head;
    while(queue->size != 0)
    {
        temp_head = queue->head->next;
        free(queue->head);
        queue->head = temp_head;
        queue->size--;
    }
    free(queue);
}

void push_JobQueue(JobQueueP jQueue, JobP toAdd)
{
    /*Create a new JobNode*/
    JobNodeP temp_node = (JobNodeP)malloc(sizeof(struct JobNode));
    /*Set the job value*/
    temp_node->job = toAdd;
    temp_node->next = NULL;
    /*tell the tail we have someone new*/
    if(jQueue->size == 0)
    {
        jQueue->head = temp_node;
        jQueue->tail = temp_node;
    }
    else
    {
        jQueue->tail->next = temp_node;
        jQueue->tail = temp_node;
    }
    jQueue->size++;
}

JobP pop_JobQueue(JobQueueP jQueue)
{
    JobP return_val = NULL;
    JobNodeP temp_head;
    if(jQueue->size != 0)
    {
        jQueue->size--;
        temp_head = jQueue->head;
        return_val = temp_head->job;
        jQueue->head = jQueue->head->next;
        free(temp_head);
    }
    return return_val;
}

int isEmpty_JobQueue(JobQueueP jQueue)
{
    if(jQueue->size == 0)
    {
         return 1;
    }
    else
    {
        return 0;
    }
}

void print_JobQueue(JobQueueP jQueue)
{
    JobNodeP temp_head = jQueue->head;
    int count = 0;
    while(temp_head != NULL)
    {
        printf("%i:%s,",count, temp_head->job->cmd_name);
        temp_head = temp_head->next;
        count ++;
    }
    printf("\n");
}
