#include "schedule.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "binaryTree.h"
#define CONTEXT_SWITCH 1
/*Static scheduler variables*/
/*Priority queue for */
static JobTreeNodeP PQ;
/*Time that it started CPU*/
static int start_time;
/*current job receiving CPU*/
static JobP current_job;

void schedule_init()
{
  PQ = create_jobTree();
  start_time =-1;
  current_job = NULL;
}

void needs_CPU(int current_time,JobP toAdd)
{
    if(start_time == -1)/*Nothing is there*/
    {
        current_job = toAdd;
        /*It cana start only after 1ms of being switched in*/
        start_time = current_time+CONTEXT_SWITCH;
    }
    else
    {
        if(toAdd->time_remaining < current_job->time_remaining)
        {
            current_job->time_remaining -= current_time - start_time;
            insert_JobTree(&PQ, current_job);
	    current_job = toAdd;
            start_time = current_time+CONTEXT_SWITCH;
        }
        else
        {
            insert_JobTree(&PQ, toAdd);
        }
    }
}

int next_CPU(int current_time)
{
    int time_to_IO = INT_MAX;
    if(start_time == -1)
    {
        return INT_MAX;
    }
    else
    {
        if(current_job->IO_interval == 0)
        {
             return start_time + current_job->time_remaining + CONTEXT_SWITCH - current_time;
        }
        else
        {
            time_to_IO = (current_job->time_remaining-(current_time-start_time)) % (int)current_job->IO_interval;
            if(time_to_IO == 0 && current_time==start_time)
            {
                time_to_IO = (int)current_job->IO_interval;
            }
            /*return the min*/
            return time_to_IO + CONTEXT_SWITCH;
        }
    }
}

JobP CPU_finished(int current_time)
{
    JobP returnVal = current_job;
    /*update how much CPU is left*/
    /*Since we dont release the JOB until endTime+1, the clock is one ahead of the switch out*/
    current_job->time_remaining -= ((current_time-CONTEXT_SWITCH) - start_time);
  
    /* if current_job needs I/O or has 0 time left, send to main, otherwise, add to back readyqueue */ 
    if (current_job->time_remaining > 0 && current_job->IOOperations == 0) {
        insert_JobTree(&PQ, current_job);
        returnVal=NULL;
    }
    /*Set up the next guy*/
    start_time = -1;
    current_job = get_NextJob(&PQ);
    
    if(current_job != NULL)
    {
        //printf("Tree Head is now:%s\n", current_job->cmd_name);
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
    if(current_job != NULL)
    {
        printf("on CPU:%s IO:%f TimeLeft:%i\n",current_job->cmd_name, current_job->IOOperations, current_job->time_remaining);
        print_Tree(PQ);
    }
}
