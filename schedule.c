#include <stdio.h>

static Job current_job;

void schedule_init(){

}

int timeTilCurrentCompletes(int current_time){
  int timeTilNextIO;
  /* ends either at next I/O or timeslice end, whichever comes soonest */
  /* no timeslices just when next I/O is */

   timeTilNextIO = current_job->time_remaining % current_job->IO_interval;  
        

    /* doesn't matter if they're the same, since we'll check in main if the
      current job needs to do IO, just need to get a number for when current
      job ends */

}

void contextSwitch(){
  /* update current job's variables */
  /* get the next job from the queue */
  /* put the current job on the queue */
}
