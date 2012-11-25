#include <stdio.h>

static Job current_job;
static JobQueue readyQueue;

void schedule_init(){
  readyQueue = create_JobQueue();  
  current_job = NULL;
}

int timeTilCurrentCompletes(int current_time){
  int timeTilNextIO;
  int timeTilNextSlice;
  int returnVal;
  /* ends either at next I/O or timeslice end, whichever comes soonest */
  /* no timeslices just when next I/O is */

  timeTilNextIO = current_job->time_remaining % current_job->IO_interval;  
  
  /* for now */
  timeTilNextSlice = current_job->time_remaining;        

  /* doesn't matter if they're the same, since we'll check in main if the
      current job needs to do IO, just need to get a number for when current
      job ends */
  if (timeTilNextIO > timeTilNextSlice) {
    returnVal = timeTilNextSlice;
  } else {
    returnVal = timeTilNextIO;
  } 
  
  return returnVal; 
}




void addJob(Job newjob){
  push_JobQueue(readyQueue, newjob);
}

void contextSwitch(int current_time){
  /* update current job's variables */
  /* get the next job from the queue */
  /* put the current job on the queue */
  current_job->time_remaining -= (current_time - current_job->start_time); 
  addJob(current_job);
  current_job = pop_JobQueue(readyQueue);
  current_job->start_time = current_time;
}
