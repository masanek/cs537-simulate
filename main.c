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
    }
    return 0;
}
