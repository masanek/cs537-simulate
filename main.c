#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "job_loader.h"
#include "IO_manager.h"


int main()
{
    int clock = 0;
    int running = 1;
    int time_CPU;
    int time_IO;
    int time_Arrival;
    int noMoreJobs = 1;
    int min;
    /*Job for arrivals*/
    Job temp_job;
    /*Initialize Job Loader*/
    next_job(-1);
    /*Initialize IO_manager*/
    IO_init();
    /*Initialize the Scheduler*/
    /*Schedualer_Init()*/
    /*Enter the main loop*/
    while(running)
    {
        /*time_CPU = next_FinishCPU(clock)*/
        time_IO = next_CompletedIO(clock);
        /*Must account for if we are at the end of the file*/
        if(noMoreJobs == 0)
        {
            time_Arrival = next_JobArrival(clock);
        }
        if(time_Arrival == -1)
        {
            noMoreJobs = 1;
            time_Arrival = INT_MAX;
        }
        /*increment clock the smallest needed*/
        min = (time_IO < time_Arrival) ? time_IO : time_Arrival;
        clock += (time_CPU < min) ? time_CPU : min;
        if(time_CPU <= time_IO && time_CPU <= time_Arrival)
        {
            /*Handle context switch*/
            /*Add to IO if needed*/
        }
        if(time_IO <= time_Arrival && time_IO <= time_CPU)
        {
            /*Handle finishing IO*/
            temp_job = IO_finished(clock);
        }
        if(time_Arrival <= time_IO && time_Arrival <= time_CPU)
        {
            /*Handle arriving Jobs*/
            do{
                temp_job = next_job(clock);
                /*needs_CPU(temp_job)*/
            }while(temp_job != NULL);
        }
        clock++;
    }
    return 0;
}
