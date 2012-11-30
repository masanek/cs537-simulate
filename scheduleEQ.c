#include "scheduleEQ.h"
#include "exp_queue.h"
#include <stdio.h>
#include <limits.h>
#include <math.h>

/*current job receiving CPU*/
static JobP current_job;
/*FIFO queue*/
static ExpQueueP readyQueue;
/*Time that it started CPU*/
static int start_time;
/*Switch in or out costs 1 ms*/
static int time_slice;
/*index of array of JobQueues for ExpQueue*/
static int priorityLevel;

#define CONTEXT_SWITCH 1

void schedule_init(){
    readyQueue = create_ExpQueue();  
    current_job = NULL;
    start_time = -1;
    priorityLevel = 0;
    time_slice = 0;
}

void needs_CPU(int current_time, JobP toAdd)
{
    if(start_time == -1)/*Nothing is there*/
    {
        current_job = toAdd;
        /*It can start only after 1ms of being switched in*/
        start_time = current_time+CONTEXT_SWITCH;
    }
    else
    {
        push_ExpQueue(readyQueue, toAdd);
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

        /*determine tme_slice length*/
        time_slice = 10 * (int)(pow(2, current_job->priorityLevel)); 

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
        return (time_to_finish < time_to_slice) ? time_to_finish + CONTEXT_SWITCH : time_to_slice + CONTEXT_SWITCH;
    }
}

JobP CPU_finished(int current_time){
    JobP returnVal = current_job;
    /*So this is tricky. need to see if we are hitting IO or ending time slice*/
    int time_ran_for = current_time-start_time;

    /* if ran for < half of timeslice, increase priority */
    if (((double)time_ran_for/time_slice) < .5) {
      if (current_job->priorityLevel != 0) current_job->priorityLevel--;
    } 
    /* ran for entire timeslice, decrease priority */
    if ((time_ran_for/time_slice) == 1) {
      if (current_job->priorityLevel != 7) current_job->priorityLevel++;
    } 


    current_job->time_remaining -= time_ran_for;
  
    /* if current_job needs I/O or has 0 time left, send to main, otherwise, add to back readyqueue */ 
    if (current_job->needs_IO == 0 && current_job->time_remaining > 0){
        push_ExpQueue(readyQueue, current_job);
        returnVal = NULL;
    }

    
    /*Set up the next guy*/
    start_time = -1;
    current_job = pop_ExpQueue(readyQueue);
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

void print_schedule_manager()
{
    int i;
    printf("*Schedule*\n");
    for(i = 0; i < 8; i++){
      printf("priority queue #%i:", i);
      print_JobQueue(readyQueue->queue[i]);
    }
    if(current_job != NULL)
    {
       printf("current:%s IO:%f TimeLeft:%i\n",current_job->cmd_name, current_job->IOOperations, current_job->time_remaining);
    }
}
