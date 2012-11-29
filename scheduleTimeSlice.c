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
        /*It can start only after 1ms of being switched in*/
        /* clock will already be incremented in main */
        start_time = current_time;
    }
    else
    {
        push_JobQueue(readyQueue, toAdd);
    }
}

int next_CPU(int current_time){
    int time_to_IO = INT_MAX;
    int time_to_slice = INT_MAX;
    int time_to_finish = INT_MAX;
    if(start_time == -1)
    {
        return INT_MAX;
    }
    else
    {
        /*Compute the time to the next slice*/
        time_to_slice = time_slice - (current_time - start_time);

        /*keep time remaining updated with time passed*/
        time_to_IO = current_job->IO_interval - (current_time - start_time); 
        
        /* will process terminate */
        time_to_finish = current_job->time_remaining - (current_time - start_time);
        printf("current_time:%i start_time:%i\n", current_time, start_time);
        printf("time_to_slice:%i time_to_IO:%i time_to_finish:%i\n", time_to_slice, time_to_IO, time_to_finish);
        /* if time_to_IO is min return it and set needs_IO to 1 */
        if(time_to_IO <= time_to_slice && time_to_IO <= time_to_finish && current_job->IOOperations > 0){
            current_job->needs_IO = 1;
            return time_to_IO;
        }

        /* otherwise return whichever happens first, process termination or timeslice ending*/
        return (time_to_finish < time_to_slice) ? time_to_finish : time_to_slice;
    }
}

JobP CPU_finished(int current_time){
    JobP returnVal = current_job;
    /*update how much CPU is left*/
    current_job->time_remaining -= (current_time - start_time - 1);
  
    /* if current_job needs I/O or has 0 time left, send to main, otherwise, add to back readyqueue */ 
    if (current_job->needs_IO == 0 && current_job->time_remaining > 0){
        push_JobQueue(readyQueue, current_job);
        returnVal = NULL;
    }

    
    /*Set up the next guy*/
    start_time = -1;
    current_job = pop_JobQueue(readyQueue);
    if(current_job != NULL)
    {
        start_time = current_time + 1;
        current_job->needs_IO = 0;
    }
    /*Only one job is here*/
    if(current_job == returnVal)
    {
        returnVal=NULL;
    }
    return returnVal;
}

JobP getCurrentJob(){
    return current_job;
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
