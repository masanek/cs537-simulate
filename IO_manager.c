#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "IO_manager.h"

/*The queue for jobs waiting for IO*/
static JobQueueP waiting_jobs;
/*Current job handling IO*/
static JobP current_job;
/*Clock time when entered IO*/
static int time_started;

void IO_init()
{
    waiting_jobs = create_JobQueue();
    current_job = NULL;
    time_started = -1;
}

void needs_IO(int current_time, JobP toAdd)
{
    /*If there is nobody waiting*/
    if(current_job == NULL)
    {
        current_job = toAdd;
        time_started = current_time;
    }
    else
    {
        /*Add to waiting queue*/
        push_JobQueue(waiting_jobs, toAdd);
    }
}

int next_CompletedIO(int current_time)
{
    /*This is true is current_job == NULL*/
    if(time_started != -1)
    {
        /*IO always takes 10 seconds*/
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
        /*And return saying IO handled the switch*/
        return_val = NULL;
    } 
    /*Set up next job to run, if there is one*/
    time_started = -1;
    current_job = pop_JobQueue(waiting_jobs);
    if(current_job != NULL)
    {
        time_started = current_time;
    }
    /*If just one job with only IO left dont return anything*/
    if(current_job == return_val)
    {
        return_val = NULL;
    }
    return return_val;
}

void print_IO_manager()
{
    printf("*IO*\n");
    print_JobQueue(waiting_jobs);
    if(current_job != NULL)
    {
       printf("current:%s IO:%f TimeLeft:%i\n",current_job->cmd_name, current_job->IOOperations, current_job->time_remaining);
    }
}


