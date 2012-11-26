#include <stdio.h>
#include <limits.h>

#include "schedule.h"
static JobP current_job;
static JobQueueP readyQueue;
static int start_time; /* start time of current job*/
/*statix int time_slice Time slice of current Job*/
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
        start_time = current_time+CONTEXT_SWITCH;/*Not sure if this is right*/
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
        /*Since we are only doing FIFO otherwise below*/
        return start_time + current_job->IO_interval + CONTEXT_SWITCH - current_time;
        /*
            int min = current_job->timeTillNextIO<timeSlice ? current_job->timeTillNextIO : timeSlice
        */
    }
  

  /* for now 
  timeTilNextSlice = current_job->time_remaining;        

   doesn't matter if they're the same, since we'll check in main if the
      current job needs to do IO, just need to get a number for when current
      job ends 
  if (timeTilNextIO > timeTilNextSlice) {
    returnVal = timeTilNextSlice;
  } else {
    returnVal = timeTilNextIO;
  } 
  
  return returnVal; */
}

JobP CPU_finished(int current_time){
    JobP returnVal = NULL;
  
    current_job->time_remaining -= (current_time - start_time);
  
    /* if current_job needs I/O or has 0 time left, send to main, otherwise, add to readyqueue */ 
    if (current_job->time_remaining == 0 || current_job->IOOperations > 0) {
        returnVal = current_job;
    }
    else
    {
        push_JobQueue(readyQueue, current_job);
    }
    start_time = -1;
    current_job = pop_JobQueue(readyQueue);
    if(current_job != NULL)
    {
        start_time = current_time;
    }
    return returnVal;
}

