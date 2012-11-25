#include "stdio.h"

#include "job_loader.h"
#include "IO_manager.h"

int main()
{
    int clock = 0;
    int running = 1;
    /*Initialize Job Loader*/
    next_job(-1);
    /*Initialize IO_manager*/
    IO_init();
    /*Initialize the Scheduler*/
    /*Schedualer_Init()*/
    /*Enter the main loop*/
    while(running)
    {
        
    }
    return 0;
}
