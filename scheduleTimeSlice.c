#include "scheduleTimeSlice.h"

#include <stdio.h>
#include <limits.h>

/*current job receiving CPU*/
static JobP current_job;
/*FIFO queue*/
static JobQueueP readyQueue;
/*Time that it started CPU*/
static int start_time;
/*Switch in or out costs 1 ms*/
static int time_slice;

#define CONTEXT_SWITCH 1

void schedule_init(){
    readyQueue = create_JobQueue();  
    current_job = NULL;
    start_time = -1;
    time_slice = 20;
}

void needs_CPU(int current_time, JobP toAdd)
{
    if(start_time == -1)/*Nothing is there*/
    {
        current_job = toAdd;
        /*It cana start only after 1ms of being switched in*/
        start_time = current_time+CONTEXT_SWITCH;
    }
    else
    {
        push_JobQueue(readyQueue, toAdd);
    }
}

int next_CPU(int current_time){
    int time_to_IO = INT_MAX;
    int time_to_slice = INT_MAX;
    if(start_time == -1)
    {
        return INT_MAX;
    }
    else
    {
        /*Compute the time to the next slice*/
        time_to_slice = time_slice-(current_time-start_time);

        /*With update time we can figure out when IO happens*/
        if(current_time != start_time)
        {
            /*keep time remaining updated with time passed*/
            time_to_IO = (current_job->time_remaining-(current_time-start_time)) % (int)current_job->IO_interval;
        }
        /*return the min*/
        return time_to_IO<time_to_slice ? time_to_IO + CONTEXT_SWITCH : time_to_slice + CONTEXT_SWITCH;
    }
}

JobP CPU_finished(int current_time){
    JobP returnVal = current_job;
    /*update how much CPU is left*/
    /*So this is tricky. need to see if we are hitting IO or ending time slice*/
    if( (current_time-CONTEXT_SWITCH)-start_time != time_slice)/*Not time slice must be IO*/
    {
        /*subtract off remaining time to IO*/
        current_job->time_remaining -= current_job->time_remaining % (int)current_job->IO_interval;
    }
    else /*Must have hit timeslice end-May still need io*/
    {
        current_job->time_remaining -= time_slice;
    }
  
    /* if current_job needs I/O or has 0 time left, send to main, otherwise, add to back readyqueue */ 
    if (current_job->time_remaining > 0 && current_job->IOOperations == 0) {
        push_JobQueue(readyQueue, current_job);
        returnVal=NULL;
    }
    /*Set up the next guy*/
    start_time = -1;
    current_job = pop_JobQueue(readyQueue);
    if(current_job != NULL)
    {
        start_time = current_time+CONTEXT_SWITCH;
    }
    /*Only one job is here*/
    if(current_job == returnVal)
    {
        returnVal=NULL;
    }
    return returnVal;
}

void print_schedule_manager()
{
    printf("*Schedule*\n");
    print_JobQueue(readyQueue);
    if(current_job != NULL)
    {
       printf("current:%s IO:%f TimeLeft:%i\n",current_job->cmd_name, current_job->IOOperations, current_job->time_remaining);
    }
}
