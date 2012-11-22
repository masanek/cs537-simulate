#include "stdio.h"

#include "job_loader.h"
#include "job.h"
int main()
{
    int clock;
    Job test;
    /*Initialize all the Managers*/
    /*Grab the first job?*/
    /*Enter the main loop*/
    for(clock = 0; clock < 20; clock++)
    {
        test = next_job(clock);
        printf("%s,%i,%f,%i\n",test->cmd_name,test->start_time,test->CPU_time,test->IO_count);
    }
    return 0;
}
