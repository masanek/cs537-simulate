#include <stdlib.h>
#include "job_queue.h"
JobQueue create_JobQueue()
{
    /*Malloc the memory*/
    JobQueue temp_queue = malloc(sizeof(JobQueue));
    /*Not sure if these are necessary*/
    temp_queue->head = NULL;
    temp_queue->tail = NULL;
    temp_queue->size = 0;
    return temp_queue;
}

void destory_JobQueue(JobQueue queue)
{
    JobNode temp_head;
    while(queue->size != 0)
    {
        temp_head = queue->head->next;
        free(queue->head);
        queue->head = temp_head;
        queue->size--;
    }
    free(queue);
}

void push_JobQueue(JobQueue jQueue, Job toAdd)
{
    /*Create a new JobNode*/
    JobNode temp_node = malloc(sizeof(JobNode));
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

Job pop_JobQueue(JobQueue jQueue)
{
    Job return_val = NULL;
    JobNode temp_head;
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
