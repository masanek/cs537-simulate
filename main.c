#include "stdio.h"

#include "job_loader.h"
#include "IO_manager.h"

int main()
{
    int clock = 0;
    int running = 1;
    int time_CPU;
    int time_IO;
    int time_Arrival;
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
        time_IO = next_CompletesIO(clock);
        time_Arrival = next_JobArrival(clock);
        if(time_CPU <= time_IO && time_CPU <= time_Arrival)
        {
            /*Handle context switch*/
            /*Add to IO if needed*/
        }
        if(time_IO <= time_Arrival && time_IO <= time_CPU)
        {
            /*Handle finishing IO*/
        }
        if(time_Arrival <= time_IO && time_Arrival <= time_CPU)
        {
            /*Handle arriving Jobs*/
            do{
                temp_job = next_job(clock);
                /*needs_CPU(temp_job)*/
            }while(temp_job != NULL);
        }
    }
    return 0;
}
