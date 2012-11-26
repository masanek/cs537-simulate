#include <stdio.h>
#include <limits.h>

#include "schedule.h"
/*current job receiving CPU*/
static JobP current_job;
/*FIFO queue*/
static JobQueueP readyQueue;
/*Time that it started CPU*/
static int start_time;
/*Switch in or out costs 1 ms*/
#define CONTEXT_SWITCH 1

void schedule_init(){
    readyQueue = create_JobQueue();  
    current_job = NULL;
    start_time = -1;
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
    if(start_time == -1)
    {
        return INT_MAX;
    }
    else
    {
        /*Since we are only doing FIFO- run until you need IO and include the swtich 1ms*/
        return start_time + current_job->IO_interval + CONTEXT_SWITCH - current_time;
    }
}

JobP CPU_finished(int current_time){
    JobP returnVal = current_job;
    /*update how much CPU is left*/
    /*Since we dont release the JOB until endTime+1, the clock is one ahead of the switch out*/
    current_job->time_remaining -= ((current_time-CONTEXT_SWITCH) - start_time);
  
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
        start_time = current_time;
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
