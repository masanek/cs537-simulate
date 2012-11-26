#include <stdlib.h>
#include <limits.h>
#include "IO_manager.h"


static JobQueueP waiting_jobs;
static JobP current_job;
static int time_started;

void IO_init()
{
    waiting_jobs = create_JobQueue();
    current_job = NULL;
    time_started = -1;
}

void needs_IO(int current_time, JobP toAdd)
{
    if(isEmpty_JobQueue(waiting_jobs))
    {
        current_job = toAdd;
        time_started = current_time;
    }
    else
    {
        push_JobQueue(waiting_jobs, toAdd);
    }
}

int next_CompletedIO(int current_time)
{
    if(time_started != -1)
    {
        return 10-(current_time - time_started);
    }
    else
    {
        return INT_MAX;
    }
}

JobP IO_finished(int current_time)
{
    JobP return_val = current_job;
    current_job->IOOperations--;
    /*Check if we only have IO left*/
    if(current_job->time_remaining == 0 && current_job->IOOperations >0)
    {
        /*Add back onto the queue*/
        push_JobQueue(waiting_jobs,current_job);
        return_val = NULL;
    } 
    /*Set up next job to run, if there is one*/
    time_started = -1;
    current_job = pop_JobQueue(waiting_jobs);
    if(current_job != NULL)
    {
        time_started = current_time;
    }
    /*We only have one in queue dont send it to CPU*/
    if(current_job == return_val)
    {
        return_val = NULL;
    }
    return return_val;
}



